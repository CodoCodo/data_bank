
#ifndef _SET_CMD_HPP
#define _SET_CMD_HPP

#include <string>
#include <memory>
#include <sstream>
#include <map>
#include "label_core_command.h"
#include "common/t_common.h"
#include "util/t_util.h"

class SetCmd : public LabelCoreCommand {
  CommandObject cmd_obj_;

  std::string var_name_;
  std::string var_value_;

  void ParseCmd(const CommandObject & cmd_obj) {
    if (cmd_obj.Empty()) {
      return ;
    }
    TUtil::SplitKeyValue(cmd_obj.value, &var_name_, &var_value_);
  }

 public:
  SetCmd(const CommandObject & cmd_obj = CommandObject())
    : cmd_obj_(cmd_obj) {
    ParseCmd(cmd_obj);
  }

  virtual std::string Key() override {
    return "set";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    if (var_name_.empty()) {
      T_COMMON_CERR << "invalid command " << cmd_obj_ << std::endl;
      return ;
    }
    auto & configs = p_context->configs_;
    auto iter = configs.find(var_name_);
    if (iter == configs.end()) {
      configs.insert(std::make_pair(var_name_, var_value_));
    } else {
      iter->second = var_value_;
    }
  }

  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {
    return std::make_shared<SetCmd>(cmd_obj);
  }
};
#endif //_SET_CMD_HPP
