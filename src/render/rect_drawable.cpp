#include "rect_drawable.h"

void RectDrawable::Update(const cv::Rect & rect) {
  rect_ = rect;
}

void RectDrawable::Draw(cv::Mat & canvas, StylePanel & style_panel) {
  cv::rectangle(canvas, rect_, style_panel.FrontColor());
}