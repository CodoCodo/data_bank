#ifndef _IMAGE_PROVIDER_H
#define _IMAGE_PROVIDER_H

#include <memory>
#include "opencv2/opencv.hpp"
#include "media_access/media_info.h"

class ImageProvider;

class ImageProvider {
 public:
  virtual int Count() = 0;
  virtual cv::Mat DoGetImage(int index) = 0;

  virtual ~ImageProvider() = default;
  cv::Mat GetImage(int index);
  std::string GetMediaPath(const MediaInfo & media_info);

  static std::shared_ptr<ImageProvider> Create(const MediaInfo & media_info);
};

#endif //_IMAGE_PROVIDER_H
