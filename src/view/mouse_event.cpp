#include "mouse_event.h"

std::ostream & operator<<(std::ostream &os, const MouseEvent & obj) {
  os << obj.event_ << "\t(" << obj.x_ << " , " << obj.y_ << ")";
  return os;
}