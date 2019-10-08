#ifndef _T_UTIL_H
#define _T_UTIL_H

#include <iostream>
#include <string>
#include <vector>

namespace TUtil {
  std::vector<std::string> Split(const std::string & str, char split_char = ' ');
}

#endif // _T_UTIL_H
