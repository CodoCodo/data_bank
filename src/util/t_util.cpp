#include "util/t_util.h"
#include <sstream>
#include <vector>
#include <algorithm>

namespace TUtil {
  std::vector<std::string> Split(const std::string & str, char split_char) {
    auto *p = str.c_str();
    auto *p_end = str.c_str() + str.size();
    const char *p_content_start = nullptr;
    std::vector<std::string> result;

    enum {
      STATE_SPLIT_CHAR = 0,
      STATE_NOT_SPLIT_CHAR,
    };
    
    int state = STATE_SPLIT_CHAR;

    auto PushStr = [&](const char *_p_start, const char * _p_end) {
      std::string tmp_str;
      std::copy(_p_start, _p_end, std::back_inserter(tmp_str));
      result.push_back(tmp_str);
    };
    
    for (; p != p_end; ++p) {
      switch (state) {
        case STATE_SPLIT_CHAR:
          if (*p != split_char) {
            p_content_start = p;
            state = STATE_NOT_SPLIT_CHAR;
          }
          break;
        case STATE_NOT_SPLIT_CHAR:
          if (*p == split_char) {
            PushStr(p_content_start, p);
            state = STATE_SPLIT_CHAR;
          }
          break;
        default:
          break;
      }
    }
    if (state == STATE_NOT_SPLIT_CHAR &&
        p_content_start != nullptr) {
      PushStr(p_content_start, p_end);
    }
    return result;
  }

  void SplitKeyValue(const std::string & str, std::string * p_key, std::string * p_value) {
    if (p_key == nullptr && p_value == nullptr) {
      return;
    }
    auto space_pos = str.find_first_of(' ');

    if (p_key != nullptr) {
      *p_key = str.substr(0, space_pos);
    }
    if (p_value != nullptr) {
      if (space_pos < str.size()) {
        *p_value = str.substr(space_pos + 1);
      } else {
        *p_value = "";
      }
    }
  }
}