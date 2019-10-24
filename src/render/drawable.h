#ifndef _DRAWABLE_H
#define _DRAWABLE_H

#include "opencv2/opencv.hpp"
#include "render/style_panel.h"

class Drawable {
 public:
  virtual void Draw(cv::Mat & canvas, StylePanel & style_panel) = 0;
};

#endif //_DRAWABLE_H
