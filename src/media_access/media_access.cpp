#include "media_access.h"
#include "mysql_dao/mysql_dao.h"
#include <sstream>
#include <unordered_map>

class MediaAccessImpl : public MediaAccess {
  MysqlDao mysql_dao_;

  std::shared_ptr<MysqlResultIterator> p_media_iterator_;
  std::string latest_filter_sql_;
  std::unordered_map<int, MediaInfo> info_map_;

  bool Inited() {
    return p_media_iterator_ != nullptr;
  }

 public:
  MediaAccessImpl()
    : mysql_dao_("localhost", "root", "codocodo", "media_bank") {
  }
 
  // 设置筛选规则，规则用的sql语法，如 "select * from medias where width > 100"
  virtual void SetFilter(const std::string & filter_sql) override {
    if (p_media_iterator_ != nullptr) {
      p_media_iterator_->Free();
    }
    MysqlResultIterator iter = mysql_dao_.DoQuery(filter_sql);
    latest_filter_sql_ = filter_sql;
    info_map_.clear();
    p_media_iterator_.reset(new MysqlResultIterator(std::move(iter)));
  }

  virtual MediaInfo Get(int index) override {
    MediaInfo result;
    if (!Inited() || index < 0 || index >= MediaCount()) {
      return result;
    }

    auto ParseRow = [&](MYSQL_ROW row) -> MediaInfo {
      std::ostringstream oss;
      int cols = p_media_iterator_->GetCols();
      for (int c = 0; c < cols; ++c) {
        oss << row[c] << '\t';
      }
      std::istringstream iss(oss.str());
      MediaInfo tmp_info;
      iss >> tmp_info;
      return tmp_info;
    };

    if (index > p_media_iterator_->GetCurrentRowIndex()) {
      while (p_media_iterator_->GetCurrentRowIndex() < index) {
        auto row = p_media_iterator_->Next();
        info_map_.insert(std::make_pair(p_media_iterator_->GetCurrentRowIndex(), ParseRow(row)));
      }
    }
    auto iter = info_map_.find(index);
    return iter->second;
  }

  virtual int MediaCount() override {
    if (!Inited()) {
      return 0;
    }
    return p_media_iterator_->GetRows();
  }
};

std::shared_ptr<MediaAccess> MediaAccess::Create() {
  return std::make_shared<MediaAccessImpl>();
}

int TestMediaAccess(int argc, char *argv[]) {
  std::shared_ptr<MediaAccess> p_media_access = MediaAccess::Create();
  p_media_access->SetFilter("select * from medias");

  auto media_count = p_media_access->MediaCount();
  std::cout << "media count is " << media_count << std::endl;
  for (int i = 0; i < media_count; ++i) {
    auto && media_info = p_media_access->Get(i);
    std::cout << media_info << std::endl;
  }
  return 0;
}
