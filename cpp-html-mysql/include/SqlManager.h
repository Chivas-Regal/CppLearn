#ifndef CPPWITHMYSQL_SQLMANAGER_H
#define CPPWITHMYSQL_SQLMANAGER_H

# include <bits/stdc++.h>
# include <mysql.h>
# include "StudentInfo.h"

class SqlManager {
private:
    std::string user = "root";
    std::string pwd = "password";
    std::string host = "localhost";
    std::string db = "student";
    unsigned int port = 3306;
    MYSQL mysql;
    MYSQL_RES *res;

public:
    // 连接数据库
    void ConnectMysql ();

    // 按照 sql 语句查询 mysql
    bool QueryMysql (std::string sql);

    // 插入一行数据为 student
    bool InsertMysql (StudentInfo student);

    // 删除含student的行
    bool DeleteMysql (StudentInfo student);

    // 将含student1的行修改为student2，找不到或者修改失败返回0，否则返回1
    bool UpdateMysql (StudentInfo student1, StudentInfo student2);

    // 按照上次查询语句输出数据库
    std::vector<std::vector<std::string> > OutputMysql ();

    // 返回表行数
    int numRow ();
};


#endif //CPPWITHMYSQL_SQLMANAGER_H
