#include "mysql_dao/mysql_dao.h"
#include <iostream>

int main(int argc, char *argv[]) {
  MysqlDao mysql_dao("localhost", "root", "codocodo", "media_bank");
  auto iter = mysql_dao.DoQuery("select * from medias");
  int cols = iter.GetCols();
  while (iter.HasNext()) {
    auto row = iter.Next();
    for (int c = 0; c < cols; ++c) {
      std::cout << row[c] << '\t';
    }
    std::cout << std::endl;
  }
  return 0;
}

#if 0
// mysql 的简单查询测试
#include <cstdio>
#include <mysql/mysql.h>

using namespace std;

int main()
{
    MYSQL *conn;
    MYSQL_RES *res;   //结果集
    char server[] = "localhost";  //数据库服务器地址
    char user[] = "root";         //用户名
    char password[] = "codocodo"; //密码
    char database[] = "media_bank";    //数据库名
    conn = mysql_init(NULL);     //初始化数据库连接

    if (!mysql_real_connect(conn, server,user, password, database,
                0, NULL, 0))    //连接数据库
    {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return -1;
    }
    printf("连接成功！\n");
    char sql[] = "select * from medias";  //查询语句
    mysql_query(conn, (char*)sql);       //执行sql语句
    res = mysql_store_result(conn);      //将查询结果装进MYSQL_RES
    if (res == nullptr) {
      printf("mysql_store_result error.\n");
      exit(-1);
    }
    int rows = mysql_num_rows(res);      //获取结果行数

    printf("the number of the result is %d\n", rows);
    while(rows--)
    {
        MYSQL_ROW row = mysql_fetch_row(res); //从结果集中获取一行
        printf("%s %s\n", row[0], row[1]);  //row[0]表示第一个字段值，row[1]表示第二个字段值
    }
    mysql_free_result(res);   //查询完后记得要释放
    mysql_close(conn);
    return 0;
}
#endif 
