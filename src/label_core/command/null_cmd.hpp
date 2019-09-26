#ifndef _NULL_CMD_H
#define _NULL_CMD_H

#include "label_core_command.h"

class NullCmd : public LabelCoreCommand {
 public:
  virtual std::string Key() {
    return "null";
  };
  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) {
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const std::string & cmd_str) {
    return std::make_shared<NullCmd>(*this);
  }
};

#endif //_NULL_CMD_H
