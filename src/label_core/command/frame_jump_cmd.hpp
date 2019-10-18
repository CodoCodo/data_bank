
#ifndef _FRAME_JUMP_CMD_HPP
#define _FRAME_JUMP_CMD_HPP

#include <string>
#include <memory>
#include <sstream>
#include "label_core_command.h"

class FrameJumpCmd : public LabelCoreCommand {
  CommandObject cmd_obj_;

  int frame_offset_;
 public:
  FrameJumpCmd（const CommandObject & cmd_obj)
    : cmd_obj_(cmd_obj),
      frame_offset_(0) {
    if (!cmd_obj.empty()) {
      std::istringstream iss(cmd_obj);
      iss >> frame_offset_;
    }
  }

  virtual std::string Usage() override {
    return Key() + " media_index frame_index";
  }

  virtual std::string Key() override {
    return "frame_jump";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    if (p_image_provider_ == nullptr ||
        p_image_provider->Count() == 0) {
      return ;
    }
    int new_frame_index = p_context->frame_index_ + frame_offset_;
    if (new_frame_index >= 0 && new_frame_index < p_image_provider->Count()) {
      p_context->frame_index_ = new_frame_index;
      p_context->raw_img_ = p_context_->p_image_provider_->GetImage(new_frame_index);
    } else if (new_frame_index < 0) {
      
    }
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<FrameJumpCmd>(cmd_obj);
  }
};
#endif //_FRAME_JUMP_CMD_HPP
