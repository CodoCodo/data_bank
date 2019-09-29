#include "mysql_result_iterator.h"

MysqlResultIterator::MysqlResultIterator(MYSQL_RES *p_res)
  : next_row_index_(0),
    rows_(0),
    p_res_(p_res) {
  if (p_res_ != nullptr) {
    rows_ = mysql_num_rows(p_res_);
  }
}

MysqlResultIterator::~MysqlResultIterator() {
  Free();
}

void MysqlResultIterator::Free() {
  if (p_res_ != nullptr) {
    mysql_free_result(p_res_);
    p_res_ = nullptr;
  }
  next_row_index_ = rows_ = 0;
}

MysqlResultIterator::MysqlResultIterator(MysqlResultIterator && obj) {
  if (this != &obj) {
    next_row_index_ = obj.next_row_index_;
    rows_ = obj.rows_;
    p_res_ = obj.p_res_;
    obj.next_row_index_ = obj.rows_ = 0;
    obj.p_res_ = nullptr;
  }
}

MysqlResultIterator& MysqlResultIterator::operator=(MysqlResultIterator && obj) {
  if (this != &obj) {
    Free();
    next_row_index_ = obj.next_row_index_;
    rows_ = obj.rows_;
    p_res_ = obj.p_res_;
    obj.next_row_index_ = obj.rows_ = 0;
    obj.p_res_ = nullptr;
  }
  return *this;
}

bool MysqlResultIterator::HasNext() {
  return next_row_index_ < rows_;
}

MYSQL_ROW MysqlResultIterator::Next() {
  auto result = mysql_fetch_row(p_res_);
  ++next_row_index_;
  return result;
}

int MysqlResultIterator::GetCols() {
  return (p_res_ != nullptr) ? p_res_->field_count : 0;
}