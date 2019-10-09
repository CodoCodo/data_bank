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

#if 0
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "util/t_util.h"

int main(int argc, char *argv[]) {
  auto result = TUtil::Split("set value 1111");
  auto result1 = TUtil::Split("how are - you ");
  return 0;
}
#endif

#include <string>
#include <iostream>
#include <sstream>
#include "msgpack.hpp"

void ShowCommand(const std::string & cmd_str) {
  auto space_pos = cmd_str.find_first_of(' ');
  auto key = cmd_str.substr(0, space_pos);
  std::string value;
  if (space_pos < cmd_str.size()) {
    value = cmd_str.substr(space_pos + 1);
  }
  std::cout << key << std::endl;
  std::cout << value << std::endl;
}

int main(int argc, char *argv[]) {
  ShowCommand("set");
  ShowCommand("set ");
  ShowCommand("set 1");
  return 0;
}
