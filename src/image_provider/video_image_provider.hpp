#ifndef _VIDEO_IMAGE_PROVIDER_H
#define _VIDEO_IMAGE_PROVIDER_H

#include "image_provider.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "image_buffer.hpp"
#include "common/t_common.h"

class VideoImageProvider : public ImageProvider {
  const int kImageBufferSize;
  cv::Mat img_;
  MediaInfo media_info_;

  int next_capture_index_;
  std::shared_ptr<cv::VideoCapture> p_video_capture_;

  ImageBuffer image_buffer_;
 public:
  VideoImageProvider(const MediaInfo & media_info)
    : kImageBufferSize(100),
      media_info_(media_info),
      next_capture_index_(0),
      p_video_capture_(std::make_shared<cv::VideoCapture>(GetMediaPath(media_info))),
      image_buffer_(kImageBufferSize) {
  }

  virtual int Count() override {
    if (!p_video_capture_->isOpened()) {
      T_COMMON_CERR << "capture open failed " << media_info_ << std::endl;
      return 0;
    }
    return media_info_.frame_cnt_;
  }

  virtual cv::Mat DoGetImage(int index) override {
    // 在缓存中查找index对应的帧
    cv::Mat image;
    if (image_buffer_.Find(index, &image)) {
      return image;
    }

    cv::Mat tmp_image;
    if (index < image_buffer_.MinIndex()) {
      p_video_capture_.reset(new cv::VideoCapture(GetMediaPath(media_info_)));
      next_capture_index_ = 0;
      image_buffer_.Clear();
    }
      
    while (index > image_buffer_.MaxIndex()) {
      *p_video_capture_ >> tmp_image;
      ++next_capture_index_;
      image_buffer_.Push(next_capture_index_ - 1, tmp_image);
    }

    image_buffer_.Find(index, &image);
    return image;
  }
};

#endif //_VIDEO_IMAGE_PROVIDER_H
