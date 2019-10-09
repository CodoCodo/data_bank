#ifndef _COMMAND_OBJECT_H
#define _COMMAND_OBJECT_H

#include <iostream>
#include <string>
#include "msgpack.hpp"

class CommandObject {
  friend std::ostream & operator<<(std::ostream & os, const CommandObject & obj);
 public:
  CommandObject(const std::string & _key = "", const std::string & _value = "");

  void Parse(const std::string & cmd_str);
  bool Empty() const;

  std::string key;
  std::string value;
  //std::vector<char> additional_buffer;
};

#endif //_COMMAND_OBJECT_H
