
#ifndef _SHOW_CMD_HPP
#define _SHOW_CMD_HPP

#include <string>
#include <memory>
#include <sstream>
#include "label_core_command.h"

class ShowCmd : public LabelCoreCommand {
  std::string cmd_str_;
  std::string key_;
  std::string var_name_;
   
  void ParseCmd(const std::string & cmd_str) {
    std::istringstream iss(cmd_str);
    iss >> key_ >> var_name_;
  }
 public:
  ShowCmd(const std::string & cmd_str = "")
    : cmd_str_(cmd_str) {
    ParseCmd(cmd_str);
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

  virtual std::shared_ptr<LabelCoreCommand> Clone(const std::string & cmd_str) override {
    return std::make_shared<ShowCmd>(cmd_str);
  }
};
#endif //_SHOW_CMD_HPP
