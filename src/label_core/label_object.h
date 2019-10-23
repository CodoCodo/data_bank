#ifndef _LABEL_OBJECT_H
#define _LABEL_OBJECT_H

#include "render/drawable.h"
#include <string>

class LabelObject : public Drawable {
  std::string label_str_;        // 标注对象的标识字符串
  cv::Rect region_;              // 标注对象的区域
 public:
  virtual ~LabelObject() = default;

  virtual void SetLabelStr(const std::string & label_str);
  virtual std::string GetLabelStr() const;

  virtual void SetRegion(const cv::Rect &region);
  virtual cv::Rect GetRegion();
};

#endif //_LABEL_OBJECT_H
