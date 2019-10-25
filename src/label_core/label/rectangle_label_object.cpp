#include "rectangle_label_object.h"

RectangleLabelObject::RectangleLabelObject() 
  : LabelObject(LabelObject::Rectangle) {
}

void RectangleLabelObject::SetRegion(const cv::Rect &region) {
  rect_ = region;
}

void RectangleLabelObject::Draw(cv::Mat & canvas, StylePanel & style_panel) {
  cv::rectangle(canvas, rect_, style_panel.FrontColor(), style_panel.Thickness());
}