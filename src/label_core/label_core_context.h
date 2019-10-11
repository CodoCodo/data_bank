#ifndef _LABEL_CORE_CONTEXT_H
#define _LABEL_CORE_CONTEXT_H

#include "opencv2/opencv.hpp"
#include "mysql_dao/mysql_dao.h"
#include "media_access/media_access.h"
#include "image_provider/image_provider.h"

class LabelCoreContext{
 public:
  LabelCoreContext();

  // 配置表
  std::map<std::string, std::string> configs_;

  // 工作状态
  typedef enum {
    IDLE = 0,
    WORKING,
  } State;
  State state_;

  // 媒体访问器
  int media_index_;
  std::shared_ptr<MediaAccess> p_media_access_;

  // 图像提供器
  int frame_index_;
  std::shared_ptr<ImageProvider> p_image_provider_;

  cv::Mat raw_img_;
    
  bool b_run_;
  cv::Mat default_background_;
  cv::Mat output_img_;
};

#endif //_LABEL_CORE_CONTEXT_H
