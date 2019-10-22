
#ifndef _FRAME_JUMP_HPP
#define _FRAME_JUMP_HPP

#include <string>
#include <memory>
#include "label_core_command.h"
#include "common/t_common.h"

class FrameJump : public LabelCoreCommand {
  int delta_index_;

  void ParseCmd(const CommandObject & cmd_obj) {
    delta_index_ = 0;
    std::istringstream iss(cmd_obj.value);
    iss >> delta_index_;
  }
 public:
  FrameJump(const CommandObject & cmd_obj = CommandObject())
    : delta_index_(0) {
    ParseCmd(cmd_obj);
  }

  virtual std::string Key() override {
    return "frame_jump";
  }

  virtual std::string Usage() override {
    return "frame_jump delta_index";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    auto res = p_context->FrameJump(delta_index_);
    T_COMMON_COUT << res << '\t' << p_context->frame_index_ << '\t' << p_context->p_image_provider_->Count() << std::endl;
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<FrameJump>(cmd_obj);
  }
};
#endif //_FRAME_JUMP_HPP
