#ifndef _IMAGE_BUFFER_H
#define _IMAGE_BUFFER_H

#include <map>
#include "opencv2/opencv.hpp"

class ImageBuffer {
  const int max_buffer_size_;
  std::map<int, cv::Mat> buffer_;
 public:
  ImageBuffer(int max_buffer_size)
    : max_buffer_size_(max_buffer_size) {
  }

  bool Find(int index, cv::Mat * p_image) {
    auto iter = buffer_.find(index);
    if (iter == buffer_.end()) {
      return false;
    }
    if (p_image != nullptr) {
      *p_image = iter->second;
    }
    return true;
  }

  void Push(int index, cv::Mat image) {
    if (Find(index, nullptr)) {
      return ;
    }
    cv::Mat tmp;
    image.copyTo(tmp);
    buffer_.insert(std::make_pair(index, tmp));

    for (auto iter = buffer_.begin(); 
         iter != buffer_.end() && buffer_.size() > max_buffer_size_;) {
      iter = buffer_.erase(iter);
    }
  }

  int MinIndex() {
    if (buffer_.empty()) {
      return -1;
    }
    return buffer_.begin()->first;
  }

  int MaxIndex() {
    if (buffer_.empty()) {
      return -1;
    }
    return buffer_.rbegin()->first;
  }

  void Clear() {
    buffer_.clear();
  }
};

#endif //_IMAGE_BUFFER_H
