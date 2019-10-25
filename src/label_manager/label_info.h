#ifndef _LABEL_INFO_H
#define _LABEL_INFO_H

#include <string>

class LabelInfo {
 public:
  typedef enum {
    Nothing,
    Point,
    Elipse,
    Circle,
    Rectangle,
    Square,
    FullScreen,
    LabelTypeCount
  } LabelType;

  int id_;
  int media_id_;
  int frame_id_;
  LabelType type_;
  std::string geometry_;
  std::string label_str_;

  LabelInfo();
  LabelInfo(int media_id,
            int frame_id,
            const LabelType & type, 
            const cv::Point & pt_start, 
            const cv::Point & pt_end,
            const std::string);

};

#endif //_LABEL_INFO_H
