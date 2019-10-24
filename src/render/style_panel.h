#ifndef _STYLE_PANEL_H
#define _STYLE_PANEL_H

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"

class StylePanel {
 public:
  virtual cv::Scalar FrontColor();
  virtual cv::Scalar BackgroundColor();
};

#endif //_STYLE_PANEL_H
