#ifndef _LABEL_CORE_CONTEXT_H
#define _LABEL_CORE_CONTEXT_H

#include "opencv2/opencv.hpp"

class LabelCoreContext{
 public:
  LabelCoreContext();
  
  bool b_run_;
  cv::Mat output_img_;
};

#endif //_LABEL_CORE_CONTEXT_H
