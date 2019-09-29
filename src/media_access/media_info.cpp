#include "media_info.h"

MediaInfo::MediaInfo()
  : id_(0),
    width_(0),
    height_(0),
    channels_(0),
    frame_cnt_(0) {
}

std::istream & operator>>(std::istream & is, MediaInfo & obj) {
  is >> obj.id_ >> obj.location_ >> obj.checksum_ >> obj.modify_date_ 
     >> obj.width_ >>  obj.height_ >> obj.channels_ >> obj.frame_cnt_;
  return is;
}

std::ostream & operator<<(std::ostream & os, MediaInfo & obj) {
  os << obj.id_ << '\t'
     << obj.location_ << '\t'
     << obj.checksum_ << '\t'
     << obj.modify_date_ << '\t'
     << obj.width_ << '\t'
     << obj.height_ << '\t'
     << obj.channels_ << '\t'
     << obj.frame_cnt_ << '\t';
  return os;
}
