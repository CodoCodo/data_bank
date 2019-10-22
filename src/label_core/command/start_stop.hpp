
#ifndef _START_STOP_HPP
#define _START_STOP_HPP

#include <string>
#include <memory>
#include "label_core_command.h"
#include "start_cmd.hpp"
#include "stop_cmd.hpp"

class StartStop : public LabelCoreCommand {
 public:
  virtual std::string Key() override {
    return "start_stop";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    if (p_context->state_ == LabelCoreContext::WORKING) {
      StopCmd cmd;
      cmd.Execute(p_context);
    } else {
      StartCmd cmd;
      cmd.Execute(p_context);
    }
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<StartStop>(*this);
  }
};
#endif //_START_STOP_HPP
