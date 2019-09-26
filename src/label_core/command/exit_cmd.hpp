
#ifndef _EXIT_CMD_HPP
#define _EXIT_CMD_HPP

#include <memory>
#include "label_core_command.h"

class ExitCmd : public LabelCoreCommand {
 public:
  virtual std::string Key() override {
    return "exit";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    p_context->b_run_ = false;
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const std::string & cmd_str) override {
    return std::make_shared<ExitCmd>(*this);
  }
};
#endif //_EXIT_CMD_HPP
