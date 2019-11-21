#ifndef _LABEL_CORE_CONTEXT_H
#define _LABEL_CORE_CONTEXT_H

#include "opencv2/opencv.hpp"
#include "mysql_dao/mysql_dao.h"
#include "media_access/media_access.h"
#include "image_provider/image_provider.h"
#include "label_core/label_object.h"
#include "label_manager/label_manager.h"

class LabelCoreContext : public LabelManagerInterface {
 public:
  LabelCoreContext();

  // 配置表
  std::map<std::string, std::string> configs_;

  cv::Mat raw_img_;
    
  bool b_run_;
  cv::Mat default_background_;
  cv::Mat output_img_;

  void Start();
  void Stop();

  // 渲染
  void Render();

  // LabelManagerInterface接口实现
  virtual std::string GetLabelStr() override;
  virtual int GetMediaId() override;
  virtual int GetFrameId() override;
};

#endif //_LABEL_CORE_CONTEXT_H
