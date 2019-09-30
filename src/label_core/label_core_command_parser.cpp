#include "label_core_command_parser.h"

std::shared_ptr<LabelCoreCommand> LabelCoreCommandParser::ExtractCommand() {
  auto p_cmd = cmd_queue_.Pop();
  return p_cmd;
}

void LabelCoreCommandParser::PushCommandStr(const std::string & cmd_str, char * p_addition_buf) {
  cmd_queue_.Push(command_factory_.Create(cmd_str));
}