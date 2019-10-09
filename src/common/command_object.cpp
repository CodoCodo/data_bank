#include "command_object.h"

std::ostream & operator<<(std::ostream & os, const CommandObject & obj) {
  os << obj.key << ' ' << obj.value;
  return os;
}

CommandObject::CommandObject(const std::string & _key, const std::string & _value)
  : key(_key),
    value(_value) {
}

void CommandObject::Parse(const std::string & cmd_str) {
  auto space_pos = cmd_str.find_first_of(' ');
  key = cmd_str.substr(0, space_pos);
  if (space_pos < cmd_str.size()) {
    value = cmd_str.substr(space_pos + 1);
  }
}

bool CommandObject::Empty() {
  return key.empty();
}