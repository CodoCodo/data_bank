#ifndef _MOUSE_EVENT_H
#define _MOUSE_EVENT_H

#include <iostream>

class MouseEvent {
  friend std::ostream & operator<<(std::ostream &os, const MouseEvent & obj);
 public:
  typedef enum {
    MOVE = 0,
    LBTN_DOWN,
    RBTN_DOWN,
    RESERVED,
    LBTN_UP,
    RBTN_UP,
  } Event;
  
  MouseEvent(int event = 0, int x = 0, int y = 0)
    : event_(event),
      x_(x),
      y_(y) {
  }
  int event_;
  int x_;
  int y_;
};

#endif //_MOUSE_EVENT_H
