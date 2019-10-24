#include "label_core_view.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <string>
#include "util/queue_ts.hpp"
#include "io/terminal_io/terminal_io.h"
#include "io/key_io/label_core_key_io.h"

class MouseEvent {
  friend std::ostream & operator<<(std::ostream &os, const MouseEvent & obj);
 public:
  MouseEvent(int event = 0, int x = 0, int y = 0)
    : event_(event),
      x_(x),
      y_(y) {
  }
  int event_;
  int x_;
  int y_;
};

std::ostream & operator<<(std::ostream &os, const MouseEvent & obj) {
  os << obj.event_ << "\t(" << obj.x_ << " , " << obj.y_ << ")";
  return os;
}

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
    
    cv::namedWindow(process_name_);
    cv::setMouseCallback(process_name_, OnMouse, &mouse_event_queue); //调用回调函数
    while(p_context_->b_run_) {
      p_command_parser_->PushCommandStr(CommandObject("update_output"));
      p_core_->RunOnce();

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