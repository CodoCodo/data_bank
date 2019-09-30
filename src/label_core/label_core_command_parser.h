#ifndef _LABEL_CORE_COMMAND_PARSER_H
#define _LABEL_CORE_COMMAND_PARSER_H

#include <memory>
#include <string>
#include "label_core_command.h"
#include "util/queue_ts.hpp"
#include "command/label_core_command_factory.h"

class LabelCoreCommandParser {
  QueueTs< std::shared_ptr<LabelCoreCommand> > cmd_queue_;
  LabelCoreCommandFactory command_factory_;
 public:
  std::shared_ptr<LabelCoreCommand> ExtractCommand();
  
  void PushCommandStr(const std::string & cmd_str, char * p_addition_buf = nullptr);
};

#endif //_LABEL_CORE_COMMAND_PARSER_H
