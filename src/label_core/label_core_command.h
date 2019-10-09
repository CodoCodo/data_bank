#ifndef _LABEL_CORE_COMMAND_H
#define _LABEL_CORE_COMMAND_H

#include <string>
#include <memory>
#include "label_core_context.h"
#include "common/command_object.h"

class LabelCoreCommand {
 public:
  virtual ~LabelCoreCommand() = default;
  virtual std::string Key() = 0;
  virtual std::string Usage() {}
  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) = 0;
  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & command_obj) = 0;
};

#endif //_LABEL_CORE_COMMAND_H
