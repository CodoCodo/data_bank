#include "label_core_context.h"
#include "common/t_common.h"
#include "common/label_core_defs.h"

LabelCoreContext::LabelCoreContext()
  : state_(IDLE),
    media_index_(0),
    p_media_access_(MediaAccess::Create()),
    b_run_(true),
    default_background_(480, 480, CV_8UC3) {
}

int LabelCoreContext::GetMediaCount() {
  return p_media_access_->MediaCount();
}

// 返回实际跳转的媒体数目
int LabelCoreContext::MediaJump(int index_delta) {
  int new_media_index = media_index_ + index_delta;
  int media_count = GetMediaCount();
  new_media_index = (new_media_index >= media_count) ? media_count - 1 :
                    ((new_media_index < 0) ? 0 : new_media_index);
  int res_delta = new_media_index - media_index_;

  if (res_delta == 0) {
    return res_delta;
  }

  media_index_ = new_media_index;
  MediaInfo && media_info = p_media_access_->Get(media_index_);

  ResetImageProvider(media_info);
  raw_img_ = p_image_provider_->GetImage(frame_index_);
  return res_delta;
}

// 帧跳转，返回实际跳转的帧数目
int LabelCoreContext::FrameJump(int index_delta) {
  int new_frame_index = frame_index_ + index_delta;
  int frame_count = p_image_provider_->Count();
  new_frame_index = (new_frame_index >= frame_count) ? frame_count - 1 :
                    ((new_frame_index < 0) ? 0 : new_frame_index);
  int res_delta = new_frame_index - frame_index_;

  if (res_delta == 0) {
    return res_delta;
  }
  frame_index_ = new_frame_index;
  raw_img_ = p_image_provider_->GetImage(frame_index_);
  return res_delta;
}

void LabelCoreContext::ResetImageProvider(const MediaInfo & media_info) {
  frame_index_ = 0;
  p_image_provider_ = ImageProvider::Create(media_info);
}

void LabelCoreContext::Start() {
  state_ = WORKING;
  auto GetMediaFilterString = [&]()-> std::string {
    auto iter = configs_.find("media_filter");
    if (iter == configs_.end()) {
      std::ostringstream oss;
      oss << "select * from " << LabelCoreDefs::GetMediaTableName();
      return oss.str();
    } else {
      return iter->second;
    }
  };

  // 设置媒体访问过滤
  media_index_ = 0;
  p_media_access_->SetFilter(GetMediaFilterString());

  // 初始化图像提供器
  ResetImageProvider(p_media_access_->Get(media_index_));

  // 初始化raw_img_
  raw_img_ = p_image_provider_->GetImage(frame_index_);

  // work here 其他初始化
}

void LabelCoreContext::Stop() {
  state_ = IDLE;
}

void LabelCoreContext::Render() {
  if (state_ == LabelCoreContext::IDLE) {
    default_background_.copyTo(output_img_);
  } else {
    raw_img_.copyTo(output_img_);
  }
}