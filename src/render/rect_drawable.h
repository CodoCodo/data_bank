#ifndef _RECT_DRAWABLE_H
#define _RECT_DRAWABLE_H

#include "render/drawable.h"

class RectDrawable : public Drawable {
  cv::Rect rect_;
 public:
  void Update(const cv::Rect & rect);
  virtual void Draw(cv::Mat & canvas, StylePanel & style_panel) override;
};

#endif //_RECT_DRAWABLE_H
