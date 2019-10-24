#ifndef _MOUSE_EVENT_LISTENER_H
#define _MOUSE_EVENT_LISTENER_H

#include <iostream>
#include "opencv2/opencv.hpp"
#include "mouse_event.h"

class MouseEventListener {
 public:
  typedef enum {
    IDLE = 0,
    LBUTTON_DOWN,
  } State;

  typedef enum {
    NONE = 0,
    LBUTTON_INPUT,
  } InputState;

  State state_;
  cv::Point pt_;
  cv::Point pt_lbutton_down_;
  cv::Point pt_lbutton_up_;

  MouseEventListener();
  InputState OnEvent(const MouseEvent & mouse_event);
};

#endif //_MOUSE_EVENT_LISTENER_H
