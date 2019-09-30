#include "label_core_command.h"
#include "label_core_command_factory.h"
#include <algorithm>
#include "null_cmd.hpp"
#include "init_cmd.hpp"
#include "exit_cmd.hpp"
#include "set_cmd.hpp"
#include "show_cmd.hpp"

LabelCoreCommandFactory::LabelCoreCommandFactory() {
  auto AddProto = [&](LabelCoreCommand * p_command) {
    std::shared_ptr<LabelCoreCommand> p(p_command);
    protos_.insert(std::make_pair(p->Key(), p));
  };
  // 初始化原型存储表
  AddProto(new NullCmd());
  AddProto(new ExitCmd());
  AddProto(new InitCmd());
  AddProto(new SetCmd());
  AddProto(new ShowCmd());
}

std::string LabelCoreCommandFactory::GetKeyFromCommandStr(const std::string & cmd_str) {
  auto pos = cmd_str.find_first_of(" ");
  return cmd_str.substr(0, pos);
}

std::shared_ptr<LabelCoreCommand> LabelCoreCommandFactory::Create(const std::string & cmd_str) {
  // 从str获取命令关键字
  auto key = GetKeyFromCommandStr(cmd_str);
  auto iter = protos_.find(key);
  std::shared_ptr<LabelCoreCommand> p_command_proto;
  if (iter != protos_.end()) {
    p_command_proto = iter->second;
  } else {
    p_command_proto = protos_["null"];
  }
  return p_command_proto->Clone(cmd_str);
}
