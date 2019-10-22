#include "label_core_key_io.h"
#include "common/command_object.h"
#include <map>

class LabelCoreKeyIoImpl: public LabelCoreKeyIo {
  std::map<int, CommandObject> method_table_;

 public:
  LabelCoreKeyIoImpl()
    : method_table_({
        {113, CommandObject("exit")},
        {115, CommandObject("start_stop")},
        {65361, CommandObject("frame_jump", "-1")},
        {65362, CommandObject("media_jump", "-1")},
        {65363, CommandObject("frame_jump", "1")},
        {65364, CommandObject("media_jump", "1")},
      }) {
  }
  // 按钮解析
  virtual CommandObject ParseKey(int key) override {
    auto iter = method_table_.find(key);
    if (iter != method_table_.end()) {
      return iter->second;
    }
    return CommandObject();
  }
};

std::shared_ptr<LabelCoreKeyIo> LabelCoreKeyIo::Create() {
  return std::make_shared<LabelCoreKeyIoImpl>();
}