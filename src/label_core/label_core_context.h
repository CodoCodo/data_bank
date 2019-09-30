#ifndef _LABEL_CORE_CONTEXT_H
#define _LABEL_CORE_CONTEXT_H

#include "opencv2/opencv.hpp"
#include "mysql_dao/mysql_dao.h"

class LabelCoreContext{
 public:
  LabelCoreContext();

  // 配置表
  std::map<std::string, std::string> configs_;
    
  bool b_run_;
  cv::Mat output_img_;
};

#endif //_LABEL_CORE_CONTEXT_H
