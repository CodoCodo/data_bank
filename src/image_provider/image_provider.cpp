#include "image_provider.h"
#include "simple_image_provider.hpp"
#include "video_image_provider.hpp"
#include "common/t_common.h"

std::shared_ptr<ImageProvider> ImageProvider::Create(const MediaInfo & media_info) {
  // 通过文件扩展名判断采用的ImageProvider实现
  std::shared_ptr<ImageProvider> p_default;
  const std::string & location = media_info.location_;
  auto ext_name = location.substr(location.find_last_of(".") + 1);

  if (ext_name == "bmp" || ext_name == "jpeg" || ext_name == "png" || ext_name == "jpg") {
    return std::make_shared<SimpleImageProvider>(media_info);
  } else if (ext_name == "mp4" || ext_name == "avi") {
    return std::make_shared<VideoImageProvider>(media_info);
  } else {
    T_COMMON_CERR << "not supported media format " << media_info.location_ << std::endl;
    exit(-1);
  }
  return p_default;
}

cv::Mat ImageProvider::GetImage(int index) {
  if (index < 0 || index >= Count()) {
    return cv::Mat();
  } 

  return DoGetImage(index);
}

std::string ImageProvider::GetMediaPath(const MediaInfo & media_info) {
  std::string path(MEDIA_PATH);
  return path + media_info.location_;
}
