#ifndef _MEDIA_ACCESS_H
#define _MEDIA_ACCESS_H

// 媒体随机访问器
#include <string>
#include <memory>
#include "media_access/media_info.h"

class MediaAccess;

class MediaAccess {
 public:
  virtual ~MediaAccess() = default;
  // 设置筛选规则，规则用的sql语法，如 "select * from medias where width > 100"
  virtual void SetFilter(const std::string & filter_sql) = 0;
  virtual MediaInfo Get(int index) = 0;
  virtual int MediaCount() = 0;

  static std::shared_ptr<MediaAccess> Create();
};

#endif //_MEDIA_ACCESS_H
