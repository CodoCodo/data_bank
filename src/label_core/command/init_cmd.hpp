
#ifndef _INIT_CMD_HPP
#define _INIT_CMD_HPP

#include <string>
#include <memory>
#include "label_core_command.h"

class InitCmd : public LabelCoreCommand {
 public:
  virtual std::string Key() override {
    return "init";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    // todo 
    std::cout << "initing " << std::endl;
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_str) override {
    return std::make_shared<InitCmd>(*this);
  }
};
#endif //_INIT_CMD_HPP
