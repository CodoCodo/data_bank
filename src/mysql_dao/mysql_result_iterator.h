#ifndef _MYSQL_RESULT_ITERATOR_H
#define _MYSQL_RESULT_ITERATOR_H

#include "mysql/mysql.h"

class MysqlResultIterator {
  int next_row_index_;
  int rows_;
  MYSQL_RES *p_res_;
  
 public:
  MysqlResultIterator(MYSQL_RES *p_res);
  ~MysqlResultIterator();
  MysqlResultIterator(const MysqlResultIterator & obj) = delete;
  MysqlResultIterator& operator=(const MysqlResultIterator & obj) = delete;
  MysqlResultIterator(MysqlResultIterator && obj);
  MysqlResultIterator& operator=(MysqlResultIterator && obj);

  bool HasNext();
  MYSQL_ROW Next();
  int GetCols();
  int GetRows();
  int GetCurrentRowIndex();
  void Free();
};

#endif //_MYSQL_RESULT_ITERATOR_H
