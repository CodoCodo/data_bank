
#ifndef _MEDIA_JUMP_HPP
#define _MEDIA_JUMP_HPP

#include <string>
#include <memory>
#include "label_core_command.h"
#include "common/t_common.h"

class MediaJump : public LabelCoreCommand {
  CommandObject cmd_obj_;

  int target_index_;
  void ParseCmd(const CommandObject & cmd_obj) {
    // work here to parse target_index
  }
 public:
  MediaJump(const CommandObject & cmd_obj)
    : cmd_obj_(cmd_obj),
      target_index_(0) {
    ParseCmd(cmd_obj_);
  }

  virtual std::string Key() override {
    return "media_jump";
  }

  virtual std::string Usage() override {
    return "media_jump media_index";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    if (target_index < 0 || target_index >= p_context->p_media_access_->MediaCount()) {
      T_COMMON_CERR << "target_index invalid" << std::endl;
      return;
    }
    if (target_index == p_context->media_index_) {
      return;
    }

    p_context->media_index_ = target_index_;
    auto && media_info = p_context->p_media_access_->Get(media_index_);
    p_context->frame_index_ = 0;
    p_image_provider_ = ImageProvider::Create(media_info);
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<MediaJump>(new MediaJump(cmd_obj));
  }
};
#endif //_MEDIA_JUMP_HPP
