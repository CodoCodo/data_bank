#ifndef _SIMPLE_IMAGE_PROVIDER_H
#define _SIMPLE_IMAGE_PROVIDER_H

#include "image_provider.h"

class SimpleImageProvider : public ImageProvider {
  cv::Mat img_;
 public:
  SimpleImageProvider(const MediaInfo & media_info) {
    img_ = cv::imread(GetMediaPath(media_info));
  }
  virtual int Count() override {
    return img_.empty() ? 0 : 1;
  }

  virtual cv::Mat DoGetImage(int index) override {
    return img_;
  }
};

#endif //_SIMPLE_IMAGE_PROVIDER_H
