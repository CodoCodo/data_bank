#ifndef _LABEL_MANAGER_H
#define _LABEL_MANAGER_H

#include <memory>
#include "label_manager/label_object.h"
#include "label_manager/label_info.h"

class LabelManagerInterface {
 public:
  virtual std::string GetLabelStr() = 0;
  virtual int GetMediaId() = 0;
  virtual int GetFrameId() = 0;
};

class LabelManager {
  LabelManagerInterface & interface_;     // 用于获取上下文的接口
  std::string label_str_;

  int current_type_index_;
  std::vector<LabelInfo::LabelType> candidate_label_types_;

  std::vector<LabelInfo> label_infos_;    // 标注信息
 public:
  LabelManager(LabelManagerInterface & interface)
    : interface_(interface),
      current_type_index_(0),
      candidate_label_types_({LabelInfo::Rectangle, LabelInfo::Point}) {
  }
  virtual ~LabelManager() = default;

  // 切换标记类型
  void SwitchLabelType() {
    current_type_index_ = (current_type_index_ + 1) % candidate_label_types_.size();
  }

  LabelInfo::LabelType GetLabelType() {
    return candidate_label_types_[current_type_index_];
  }

  // 添加一个标注
  void AddLabel(const cv::Point & pt_start, const cv::Point & pt_end) {
    LabelInfo label_info(interface_.GetMediaId(),
                         interface_.GetFrameId(),
                         GetLabelType(),
                         pt_start,
                         pt_end,
                         interface_.GetLabelStr());
    label_infos_.push_back(label_info);
  }

  // 删除一个标注
  void DelLabel(int label_id);
  // 获取指定id的标注
  LabelObject GetLabel(int label_id);

  static std::shared_ptr<LabelManager> Create();
};

#endif //_LABEL_MANAGER_H
