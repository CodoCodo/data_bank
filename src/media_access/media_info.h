#ifndef _MEDIA_INFO_H
#define _MEDIA_INFO_H

#include <string>
#include <iostream>

class MediaInfo {
  friend std::istream & operator>>(std::istream & is, MediaInfo & obj);
  friend std::ostream & operator<<(std::ostream & os, MediaInfo & obj);
 public:
  MediaInfo();
  
  int id_;
  std::string location_;
  std::string checksum_;
  std::string modify_date_;
  
  int width_;
  int height_;
  int channels_;
  int frame_cnt_;
};

#endif //_MEDIA_INFO_H
