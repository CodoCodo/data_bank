#ifndef _LABEL_CORE_COMMAND_FACTORY_H
#define _LABEL_CORE_COMMAND_FACTORY_H

#include <map>
#include <string>
#include <memory>
#include "common/command_object.h"

class LabelCoreCommandFactory {
  // 命令原型存储表
  std::map< std::string, std::shared_ptr<LabelCoreCommand> > protos_;
  std::string GetKeyFromCommandStr(const std::string & cmd_str);
 public:
  LabelCoreCommandFactory();
  std::shared_ptr<LabelCoreCommand> Create(const CommandObject & command_obj);
};

#endif //_LABEL_CORE_COMMAND_FACTORY_H
