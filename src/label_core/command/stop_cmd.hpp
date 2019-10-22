
#ifndef _STOP_CMD_HPP
#define _STOP_CMD_HPP

#include <string>
#include <memory>
#include "label_core_command.h"

class StopCmd : public LabelCoreCommand {
 public:
  virtual std::string Key() override {
    return "stop";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    p_context->Stop();
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<StopCmd>(*this);
  }
};
#endif //_STOP_CMD_HPP
