#ifndef _LABEL_CORE_KEY_IO_H
#define _LABEL_CORE_KEY_IO_H

#include "common/command_object.h"
#include <memory>

class LabelCoreKeyIo;

class LabelCoreKeyIo {
 public:
  virtual ~LabelCoreKeyIo() = default;
  // 按钮解析
  virtual CommandObject ParseKey(int key) = 0;

  static std::shared_ptr<LabelCoreKeyIo> Create();
};

#endif //_LABEL_CORE_KEY_IO_H
