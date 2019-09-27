#include "label_core_command_parser.h"
// #include "command/label_core_command_factory.h"

std::shared_ptr<LabelCoreCommand> LabelCoreCommandParser::ExtractCommand() {
  auto p_cmd = cmd_queue_.Pop();
  return p_cmd;
}

void PushCommandStr(const std::string & cmd_str, char * p_addition_buf = nullptr) {
}