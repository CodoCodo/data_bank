#include "command_object.h"
#include "util/t_util.h"

std::ostream & operator<<(std::ostream & os, const CommandObject & obj) {
  os << obj.key << ' ' << obj.value;
  return os;
}

CommandObject::CommandObject(const std::string & _key, const std::string & _value)
  : key(_key),
    value(_value) {
}

void CommandObject::Parse(const std::string & cmd_str) {
  TUtil::SplitKeyValue(cmd_str, &key, &value);
}

bool CommandObject::Empty() const {
  return key.empty();
}