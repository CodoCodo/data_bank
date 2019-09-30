#if 0
// Test ImageProvider and MediaAccess

#include "media_access/media_access.h"
#include "image_provider/image_provider.h"

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

int TestImageProvider(int argc, char *argv[]) {
  std::shared_ptr<MediaAccess> p_media_access = MediaAccess::Create();
  p_media_access->SetFilter("select * from medias where id=1");

  auto media_count = p_media_access->MediaCount();
  std::cout << "media count is " << media_count << std::endl;
  for (int i = 0; i < media_count; ++i) {
    auto && media_info = p_media_access->Get(i);
    auto p_provider = ImageProvider::Create(media_info);
    for (int j = p_provider->Count() - 1; j>= 0; --j) {
      cv::Mat img = p_provider->GetImage(j);
      cv::imshow(__FUNCTION__, img);
      cv::waitKey(40);
    }
  }
  return 0;
}
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> TSplit(const std::string & str, char split_char = ' ') {
  auto *p = str.c_str();
  auto *p_end = str.c_str() + str.size();
  const char *p_content_start = nullptr;

  enum {
    STATE_SPLIT_CHAR = 0,
    STATE_NOT_SPLIT_CHAR,
  };
  
  int state = STATE_SPLIT_CHAR;
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
        }
        break;
      default:
        break;
    }
    if (*p != split_char) {

    }
  }
}

int main(int argc, char *argv[]) {
  std::string tmp_str("fuck");
  std::cout << tmp_str.size() << std::endl;
  return 0;
}
