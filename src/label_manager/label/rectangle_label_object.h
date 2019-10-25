#ifndef _RECTANGLE_LABEL_OBJECT_H
#define _RECTANGLE_LABEL_OBJECT_H

#include "label_object.h"

class RectangleLabelObject : public LabelObject {
  cv::Rect rect_;
 public:
  RectangleLabelObject();
  virtual void SetRegion(const cv::Rect &region) override;

  // draw
  virtual void Draw(cv::Mat & canvas, StylePanel & style_panel) override;
};

#endif //_RECTANGLE_LABEL_OBJECT_H
