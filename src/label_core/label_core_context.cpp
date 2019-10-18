#include "label_core_context.h"
#include "common/t_common.h"

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
                    (new_media_index < 0) ? 0 : new_media_index;
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
                    (new_frame_index < 0) ? 0 : new_frame_index;
  int res_delta = new_frame_index - media_index_;

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
