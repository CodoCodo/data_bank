
#ifndef _SET_CMD_HPP
#define _SET_CMD_HPP

#include <string>
#include <memory>
#include <sstream>
#include <map>
#include "label_core_command.h"
#include "common/t_common.h"

class SetCmd : public LabelCoreCommand {
  std::string cmd_str_;

  std::string key_;
  std::string var_name_;
  std::string var_value_;

  void ParseCmd(const std::string & cmd_str) {
    if (cmd_str.empty()) {
      return ;
    }
    std::istringstream iss(cmd_str);
    iss >> key_ >> var_name_;

    // work here
  }

 public:
  SetCmd(const std::string & cmd_str = "")
    : cmd_str_(cmd_str) {
    ParseCmd(cmd_str);
  }

  virtual std::string Key() override {
    return "set";
  }

  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {
    if (var_name_.empty()) {
      T_COMMON_CERR << "invalid command " << cmd_str_ << std::endl;
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

  virtual std::shared_ptr<LabelCoreCommand> Clone(const std::string & cmd_str) override {
    return std::make_shared<SetCmd>(cmd_str);
  }
};
#endif //_SET_CMD_HPP
