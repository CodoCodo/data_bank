
#ifndef _UPDATE_OUTPUT_CMD_HPP
#define _UPDATE_OUTPUT_CMD_HPP

#include <string>
#include <memory>
#include "label_core_command.h"

class UpdateOutputCmd : public LabelCoreCommand {
 public:
  virtual std::string Key() override {
    return "update_output";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    p_context->Render();
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<UpdateOutputCmd>(*this);
  }
};
#endif //_UPDATE_OUTPUT_CMD_HPP
