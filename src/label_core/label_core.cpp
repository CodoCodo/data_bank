#include "label_core.h"
#include "label_core_context.h"
#include "media_manager.h"
#include "label_manager.h"

class LabelCoreImpl : public LabelCore {
  std::shared_ptr< QueueTs<LabelCoreCommand> > p_cmd_queue_;
  std::shared_ptr<MediaManager> p_media_manager_;
  std::shared_ptr<LabelManager> p_label_manager_;
 public:
  LabelCoreImpl(std::shared_ptr< QueueTs<LabelCoreCommand> > p_cmd_queue) {
    : p_cmd_queue_(p_cmd_queue),
      p_label_core_context_(std::make_shared<LabelCoreContext>())
      p_media_manager_(MediaManager::Create(p_label_core_context_)),
      p_label_manager_(LabelManager::Create(p_label_core_context_)) {
  }

  void Execute(const LabelCoreCommand & cmd) {
    // todo: handle commands here
  }

  virtual void RunOnce() override {
    LabelCoreCommand cmd;
    if (p_cmd_queue_->TryPop(cmd)) {
      Execute(cmd);
    }
  }
};
 
std::shared_ptr<LabelCore> LabelCore::Create(std::shared_ptr< QueueTs<LabelCoreCommand> > p_cmd_queue) {
  return std::make_shared<LabelCoreImpl>(std::shared_ptr< QueueTs<LabelCoreCommand> > p_cmd_queue);
}