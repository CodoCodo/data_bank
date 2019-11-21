#include "media_manager.h"
#include "media_access/media_access.h"
#include "image_provider/image_provider.h"
#include "label_core_context.h"
#include <sstream>
#include "common/label_core_defs.h"

class MediaManagerImpl : public MediaManager {
 public:
  std::shared_ptr<LabelCoreContext> p_context_;
  // 媒体访问器
  int media_index_;
  std::shared_ptr<MediaAccess> p_media_access_;

  // 图像提供器
  int frame_index_;
  std::shared_ptr<ImageProvider> p_image_provider_;

  MediaManagerImpl()
    : media_index_(0),
      p_media_access_(MediaAccess::Create()),
      frame_index_(0) {
  }

  virtual void Start() override {
    auto GetMediaFilterString = [&]()-> std::string {
      auto iter = p_context_->configs_.find("media_filter");
      if (iter == p_context_->configs_.end()) {
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
  }

  virtual int GetMediaCount() override {
    return p_media_access_->MediaCount();
  }

  // 返回实际跳转的媒体数目
  virtual int MediaJump(int index_delta) override {
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
    return res_delta;
  }

  // 帧跳转，返回实际跳转的帧数目
  virtual int FrameJump(int index_delta) override {
    int new_frame_index = frame_index_ + index_delta;
    int frame_count = p_image_provider_->Count();
    new_frame_index = (new_frame_index >= frame_count) ? frame_count - 1 :
                        ((new_frame_index < 0) ? 0 : new_frame_index);
    int res_delta = new_frame_index - frame_index_;

    if (res_delta == 0) {
        return res_delta;
    }
    frame_index_ = new_frame_index;
    return res_delta;
  }

  virtual void ResetImageProvider(const MediaInfo & media_info) {
    frame_index_ = 0;
    p_image_provider_ = ImageProvider::Create(media_info);
  }

  virtual cv::Mat GetImage() override {
    if (p_image_provider_ == nullptr) {
      return cv::Mat();
    } else {
      return p_image_provider_->GetImage(frame_index_);
    }
  }
};

std::shared_ptr<MediaManager> MediaManager::Create(std::shared_ptr<LabelCoreContext> p_context) {
  return std::make_shared<MediaManagerImpl>(p_context);
}