
#ifndef _START_CMD_HPP
#define _START_CMD_HPP

#include <string>
#include <memory>
#include <sstream>
#include "label_core_command.h"
#include "common/label_core_defs.h"

class StartCmd : public LabelCoreCommand {
  std::string GetMediaFilterString(std::shared_ptr<LabelCoreContext> p_context) {
    auto & configs = p_context->configs_;
    auto iter = configs.find("media_filter");
    if (iter == configs.end()) {
      std::ostringstream oss;
      oss << "select * from " << LabelCoreDefs::GetMediaTableName();
      return oss.str();
    } else {
      return iter->second;
    }
  }
 public:
  virtual std::string Key() override {
    return "start";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    // work here初始化进程状态机
    p_context->state_ = LabelCoreContext::WORKING;

    // 初始化媒体访问器
    p_context->media_index_ = 0;
    p_context->p_media_access_->SetFilter(GetMediaFilterString(p_context));

    // 初始化图像提供器
    MediaInfo && media_info = p_context->p_media_access_->Get(p_context->media_index_);
    p_context->frame_index_ = 0;
    p_context->p_image_provider_ = ImageProvider::Create(media_info);

    // 初始化raw_img_
    p_context->raw_img_ = p_context->p_image_provider_->GetImage(p_context->frame_index_);

    // 初始化标记管理器
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<StartCmd>(*this);
  }
};
#endif //_START_CMD_HPP
