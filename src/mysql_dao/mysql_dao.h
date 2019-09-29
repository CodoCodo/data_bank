#ifndef _MYSQL_DAO_H
#define _MYSQL_DAO_H

#include <stdio.h>
#include <string>
#include "mysql/mysql.h"
#include "mysql_result_iterator.h"

class MysqlDao {
  MysqlDao(const MysqlDao &) = delete;

  MYSQL *conn_;
  MYSQL_RES *res_;
  std::string server_;
  std::string user_;
  std::string password_;
  std::string database_;
 public:
  MysqlDao(const std::string & server,
           const std::string & user,
           const std::string & password,
           const std::string & database);
  ~MysqlDao();
  MysqlResultIterator DoQuery(const std::string & sql);
};

#endif //_MYSQL_DAO_H
