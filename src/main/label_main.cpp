//标注程序主函数

#include <iostream>
#include <string>
#include <memory>
#include "label_core/label_core_context.h"
#include "label_core/label_core.h"
#include "label_core/label_core_command_parser.h"

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

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

void OnMouse(int event, int x, int y, int flags, void *user_data) {
  QueueTs<MouseEvent> *p_queue = (QueueTs<MouseEvent> *)user_data;
  p_queue->Push(MouseEvent(event, x, y));
}

int LabelMain(int argc, char *argv[]) {
  const std::string process_name = "label";
  const int frame_interval = 40;
  std::shared_ptr<LabelCoreContext> p_context(new LabelCoreContext);
  std::shared_ptr<LabelCoreCommandParser> p_command_parser(new LabelCoreCommandParser);
  std::shared_ptr<LabelCore> p_core(new LabelCore(p_context, p_command_parser));
  QueueTs<MouseEvent> mouse_event_queue;

  std::shared_ptr< QueueTs<CommandObject> > p_terminal_cmd_queue = std::make_shared< QueueTs<CommandObject> >();
  TerminalIo terminal_io(p_terminal_cmd_queue);
  std::shared_ptr<LabelCoreKeyIo> p_label_core_key_io = LabelCoreKeyIo::Create();
  
  cv::namedWindow(process_name);
  cv::setMouseCallback(process_name, OnMouse, &mouse_event_queue); //调用回调函数

  while(p_context->b_run_) {
    p_command_parser->PushCommandStr(CommandObject("update_output"));
    p_core->RunOnce();

    cv::imshow(process_name, p_context->output_img_);
     
    // 按键事件
    auto key = cv::waitKey(frame_interval);
    if (key > 0) {
      std::cout << "tdj_debug " << (int)key << std::endl;
      auto && cmd_obj = p_label_core_key_io->ParseKey(key);
      p_command_parser->PushCommandStr(cmd_obj);
      p_core->RunOnce();
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
      p_command_parser->PushCommandStr(cmd_obj);
      p_core->RunOnce();
    }
  }

  cv::destroyWindow(process_name);
  return 0;
}

int main(int argc, char *argv[]) {
  return LabelMain(argc, argv);
}
