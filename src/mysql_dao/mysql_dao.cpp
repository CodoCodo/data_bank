#include "mysql_dao.h"
#include "util/t_debug_common.h"

MysqlDao::MysqlDao(const std::string & server,
                   const std::string & user,
                   const std::string & password,
                   const std::string & database)
  : conn_(nullptr),
    res_(nullptr),
    server_(server),
    user_(user),
    password_(password),
    database_(database) {
  conn_ = mysql_init(nullptr);     //初始化数据库连接
  // 连接数据库
  if (!mysql_real_connect(conn_, server_.c_str(), user_.c_str(), 
      password_.c_str(), database_.c_str(), 0, NULL, 0)) {
    T_DEBUG_CERR << mysql_error(conn_) << std::endl;
    exit(-1);
  }
}

MysqlDao::~MysqlDao() {
  mysql_close(conn_);
  conn_ = nullptr;
}

MysqlResultIterator MysqlDao::DoQuery(const std::string & sql) {
  mysql_query(conn_, sql.c_str());
  auto p_res = mysql_store_result(conn_);
  return MysqlResultIterator(p_res);
}
