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

int main(int argc, char *argv[]) {
  const std::string process_name = "label";
  const int frame_interval = 40;
  std::shared_ptr<LabelCoreContext> p_context(new LabelCoreContext);
  std::shared_ptr<LabelCoreCommandParser> p_command_parser(new LabelCoreCommandParser);
  std::shared_ptr<LabelCore> p_core(new LabelCore(p_context, p_command_parser));
  QueueTs<MouseEvent> mouse_event_queue;
  
  cv::Mat output_img;
  cv::namedWindow(process_name);
  cv::setMouseCallback(process_name, OnMouse, &mouse_event_queue); //调用回调函数
  while(1) {
    cv::imshow(process_name, p_context->output_img_);
     
    // 命令生成
    auto key = cv::waitKey(frame_interval);
    std::cout << "tdj_debug " << (int)key << std::endl;

    MouseEvent mouse_event;
    if (mouse_event_queue.TryPop(mouse_event)) {
      std::cout << "tdj_debug " << mouse_event << std::endl;
    }

    // 推送命令
  }

  cv::destroyWindow(process_name);
  return 0;
}