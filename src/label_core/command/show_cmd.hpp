
#ifndef _SHOW_CMD_HPP
#define _SHOW_CMD_HPP

#include <string>
#include <memory>
#include <sstream>
#include "label_core_command.h"

class ShowCmd : public LabelCoreCommand {
  CommandObject cmd_obj_;
  std::string var_name_;
   
  void ParseCmd(const CommandObject & cmd_obj) {
    TUtil::SplitKeyValue(cmd_obj.value, &var_name_);
  }
 public:
  ShowCmd(const CommandObject & cmd_obj = CommandObject())
    : cmd_obj_(cmd_obj) {
    ParseCmd(cmd_obj);
  }

  virtual std::string Key() override {
    return "show";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    auto & configs = p_context->configs_;
    auto iter = configs.find(var_name_);
    if (iter == configs.end()) {
      T_COMMON_COUT << Key() << " : variable not found " << var_name_ << std::endl;
    } else {
      T_COMMON_COUT << Key() << " : " << var_name_ << " " << iter->second << std::endl;
    }
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<ShowCmd>(cmd_obj);
  }
};
#endif //_SHOW_CMD_HPP
