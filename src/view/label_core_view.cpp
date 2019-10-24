#include "label_core_view.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <string>
#include "util/queue_ts.hpp"
#include "io/terminal_io/terminal_io.h"
#include "io/key_io/label_core_key_io.h"

#include "mouse_event.h"
#include "mouse_event_listener.h"
#include "render/rect_drawable.h"
#include "common/t_common.h"

class LabelCoreViewImpl : public LabelCoreView {
  const std::string process_name_ = "label";
  const int frame_interval_ = 40;
  std::shared_ptr<LabelCoreContext> p_context_;
  std::shared_ptr<LabelCoreCommandParser> p_command_parser_;
  std::shared_ptr<LabelCore> p_core_;

  static void OnMouse(int event, int x, int y, int flags, void *user_data) {
    QueueTs<MouseEvent> *p_queue = (QueueTs<MouseEvent> *)user_data;
    p_queue->Push(MouseEvent(event, x, y));
  }

  bool valid_select_region_;
  cv::Rect select_region_;

  StylePanel high_light_style_;
  RectDrawable rect_drawable_;

  cv::Rect GetSelectRegion(cv::Point & p1, cv::Point & p2) {
    cv::Rect tmp;
    tmp.x = std::min(p1.x, p2.x);
    tmp.y = std::min(p1.y, p2.y);
    tmp.width = std::abs(p1.x - p2.x);
    tmp.height = std::abs(p1.y - p2.y);
    return tmp;
  }
 public:
  LabelCoreViewImpl(std::shared_ptr<LabelCoreContext> p_context,
                    std::shared_ptr<LabelCoreCommandParser> p_command_parser,
                    std::shared_ptr<LabelCore> p_core)
    : process_name_("label"),
      frame_interval_(40),
      p_context_(p_context),
      p_command_parser_(p_command_parser),
      p_core_(p_core) {
  }

  virtual void Run() override {
    QueueTs<MouseEvent> mouse_event_queue;

    std::shared_ptr< QueueTs<CommandObject> > p_terminal_cmd_queue = std::make_shared< QueueTs<CommandObject> >();
    TerminalIo terminal_io(p_terminal_cmd_queue);
    std::shared_ptr<LabelCoreKeyIo> p_label_core_key_io = LabelCoreKeyIo::Create();
    std::shared_ptr<MouseEventListener> p_mouse_listener = std::make_shared<MouseEventListener>();
    
    cv::namedWindow(process_name_);
    cv::setMouseCallback(process_name_, OnMouse, &mouse_event_queue); //调用回调函数

    valid_select_region_ = false;
    while(p_context_->b_run_) {
      p_command_parser_->PushCommandStr(CommandObject("update_output"));
      p_core_->RunOnce();

      if (valid_select_region_) {
        rect_drawable_.Draw(p_context_->output_img_, high_light_style_);
      }
      cv::imshow(process_name_, p_context_->output_img_);
      
      // 按键事件
      auto key = cv::waitKey(frame_interval_);
      if (key > 0) {
        std::cout << "tdj_debug " << (int)key << std::endl;
        auto && cmd_obj = p_label_core_key_io->ParseKey(key);
        p_command_parser_->PushCommandStr(cmd_obj);
        p_core_->RunOnce();
      }

      // 处理鼠标事件
      MouseEvent mouse_event;
      for (int mouse_event_count = mouse_event_queue.Size();
          mouse_event_count > 0; --mouse_event_count) {
          mouse_event_queue.TryPop(mouse_event);
        auto input_state = p_mouse_listener->OnEvent(mouse_event);
        if (p_mouse_listener->state_ == MouseEventListener::LBUTTON_DOWN) {
          valid_select_region_ = true;
          select_region_ = GetSelectRegion(p_mouse_listener->pt_lbutton_down_, p_mouse_listener->pt_);
          rect_drawable_.Update(select_region_);
        } else {
          valid_select_region_ = false;
        }
      }

      for (int i = p_terminal_cmd_queue->Size();
          i > 0; --i) {
        CommandObject cmd_obj;
        p_terminal_cmd_queue->TryPop(cmd_obj);
        // 推送命令
        p_command_parser_->PushCommandStr(cmd_obj);
        p_core_->RunOnce();
      }
    }

    cv::destroyWindow(process_name_);
  }
};

std::shared_ptr<LabelCoreView> LabelCoreView::Create(std::shared_ptr<LabelCoreContext> p_context,
                                                         std::shared_ptr<LabelCoreCommandParser> p_command_parser,
                                                         std::shared_ptr<LabelCore> p_core) {
  return std::make_shared<LabelCoreViewImpl>(p_context, p_command_parser, p_core);
}