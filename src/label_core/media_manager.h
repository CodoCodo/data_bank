#ifndef _MEDIA_MANAGER_H
#define _MEDIA_MANAGER_H

#include "opencv2/opencv.hpp"
#include <memory>
#include "label_core/label_core_context.h"

class MediaManager {
 public:
  virtual void Start();

  virtual int GetMediaCount();
  // 返回实际跳转的媒体数目
  virtual int MediaJump(int index_delta);
  // 帧跳转，返回实际跳转的帧数目
  virtual int FrameJump(int index_delta);

  // 获取当前的媒体图片
  virtual cv::Mat GetImage();
  
  static std::shared_ptr<MediaManager> Create(std::shared_ptr<LabelCoreContext> p_context);
};

#endif // _MEDIA_MANAGER_H