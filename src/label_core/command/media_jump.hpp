
#ifndef _MEDIA_JUMP_HPP
#define _MEDIA_JUMP_HPP

#include <string>
#include <memory>
#include "label_core_command.h"
#include "common/t_common.h"

class MediaJump : public LabelCoreCommand {
  CommandObject cmd_obj_;

  int delta_index_;
  void ParseCmd(const CommandObject & cmd_obj) {
    delta_index_ = 0;
    std::istringstream iss(cmd_obj.value);
    iss >> delta_index_;
  }
 public:
  MediaJump(const CommandObject & cmd_obj = CommandObject())
    : cmd_obj_(cmd_obj),
      delta_index_(0) {
    ParseCmd(cmd_obj_);
  }

  virtual std::string Key() override {
    return "media_jump";
  }

  virtual std::string Usage() override {
    return "media_jump delta_index";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    p_context->MediaJump(delta_index_);
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<MediaJump>(cmd_obj);
  }
};
#endif //_MEDIA_JUMP_HPP
