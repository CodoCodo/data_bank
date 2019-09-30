#ifndef _LABEL_CORE_H
#define _LABEL_CORE_H

#include <memory>
#include "label_core_context.h"
#include "label_core_command.h"
#include "label_core_command_parser.h"

class LabelCore {
  std::shared_ptr<LabelCoreContext> p_context_;
  std::shared_ptr<LabelCoreCommandParser> p_command_parser_;
 public:
  LabelCore(std::shared_ptr<LabelCoreContext> p_context,
            std::shared_ptr<LabelCoreCommandParser> p_command_parser);
            
  void Run();

  void RunOnce();
};

#endif //_LABEL_CORE_H
