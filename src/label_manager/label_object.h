#ifndef _LABEL_OBJECT_H
#define _LABEL_OBJECT_H

#include "render/drawable.h"
#include <string>
#include <memory>

class LabelObject : public Drawable {
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

  virtual ~LabelObject() = default;

  virtual void SetLabelStr(const std::string & label_str);
  virtual std::string GetLabelStr() const;

  virtual void SetRegion(const cv::Rect &region);
  virtual cv::Rect GetRegion() const;

  static std::shared_ptr<LabelObject> Create(const LabelType & type);

 protected:
  LabelObject(const LabelType & type);

 private:
  LabelType type_;               // 标注对象的类型
  std::string label_str_;        // 标注对象的标识字符串
  cv::Rect region_;              // 标注对象的区域
};

#endif //_LABEL_OBJECT_H
