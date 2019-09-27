#include "label_core.h"

LabelCore::LabelCore(std::shared_ptr<LabelCoreContext> p_context,
                     std::shared_ptr<LabelCoreCommandParser> p_command_parser)
  : p_context_(p_context),
    p_command_parser_(p_command_parser) {
}

void LabelCore::Run() {
  while (p_context_->b_run_) {
    auto p_cmd = p_command_parser_->ExtractCommand();
    p_cmd->Execute(p_context_);
  }
}
