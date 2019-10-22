
#ifndef _START_CMD_HPP
#define _START_CMD_HPP

#include <string>
#include <memory>
#include <sstream>
#include "label_core_command.h"
#include "common/label_core_defs.h"

class StartCmd : public LabelCoreCommand {
 public:
  virtual std::string Key() override {
    return "start";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    p_context->Start();
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<StartCmd>(*this);
  }
};
#endif //_START_CMD_HPP
