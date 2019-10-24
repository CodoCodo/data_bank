#include "mouse_event_listener.h"

MouseEventListener::MouseEventListener()
  : state_(IDLE) {
}

MouseEventListener::InputState MouseEventListener::OnEvent(const MouseEvent & mouse_event) {
  InputState result = NONE;
  switch (state_) {
    case IDLE:
      if (mouse_event.event_ == MouseEvent::LBTN_DOWN) {
        pt_lbutton_down_.x = mouse_event.x_;
        pt_lbutton_down_.y = mouse_event.y_;
        pt_.x = mouse_event.x_;
        pt_.y = mouse_event.y_;
        state_ = LBUTTON_DOWN;
      }
      break;
    case LBUTTON_DOWN:
      if (mouse_event.event_ == MouseEvent::LBTN_UP) {
        pt_lbutton_up_.x = mouse_event.x_;
        pt_lbutton_up_.y = mouse_event.y_;
        pt_.x = mouse_event.x_;
        pt_.y = mouse_event.y_;
        state_ = IDLE;
        result = LBUTTON_INPUT;
      } else if (mouse_event.event_ == MouseEvent::MOVE) {
        pt_.x = mouse_event.x_;
        pt_.y = mouse_event.y_;
      }
      break;
  }
  return result;
}