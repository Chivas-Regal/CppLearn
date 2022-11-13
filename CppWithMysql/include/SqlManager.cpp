//
// Created by snopzyz on 2022/11/10.
//

#include "SqlManager.h"

void SqlManager::ConnectMysql() {
    mysql_init(&mysql);
    if (mysql_real_connect(&mysql,
                           host.c_str(),
                           user.c_str(),
                           pwd.c_str(),
                           db.c_str(), port,
                           NULL,
                           0)) {
        std::cout << "Successfully connect \'" << db << "\'" << std::endl;
    } else {
        std::cout << "Fail connect" << std::endl;
    }
}

bool SqlManager::QueryMysql(std::string sql) {
    mysql_query(&mysql, "set names utf8");
    if (mysql_query(&mysql, sql.c_str())) {
        std::cout << "Fail run \'" << sql << "\' with " << (std::string)mysql_error(&mysql) << std::endl;
        return false;
    } else {
        std::cout << "Successfully run \'" << sql << "\'" << std::endl;
    }
    if (!(res = mysql_store_result(&mysql))) {
        std::cout << "Couldn\'t get result from " << (std::string)mysql_error(&mysql) << std::endl;
        return false;
    }
    OutputMysql();
    return true;
}

void SqlManager::OutputMysql() {
    int numrow = mysql_affected_rows(&mysql);
    int numcol = mysql_num_fields(res);
    std::cout << "number of dataline returned: " << numrow << std::endl;
    for (int i = 0; i < numcol; i ++) {
        std::string curCow = mysql_fetch_field(res)->name;
        std::cout.width(10);
        std::cout << curCow + "\t|\t";
    } std::cout << std::endl;

    MYSQL_ROW mysql_row;
    while (mysql_row = mysql_fetch_row(res)) {
        for (int i = 0; i < numcol; i ++) {
            std::string curCow = mysql_row[i];
            std::cout.width(10);
            std::cout << curCow + "\t|\t";
        }
        std::cout << std::endl;
    }
}
bool SqlManager::InsertMysql(StudentInfo student) {
    std::string sql = "INSERT INTO STUDENT (Sno,Sname,Ssex,Sage,Sdept) VALUES (";
    sql += "\'" + student.getSno() + "\',";
    sql += "\'" + student.getSname() + "\',";
    sql += "\'" + student.getSsex() + "\',";
    sql += "\'" + std::to_string(student.getSage()) + "\',";
    sql += "\'" + student.getSdept() + "\')";
    mysql_query(&mysql, "set names utf8");
    if (mysql_query(&mysql, sql.c_str())) {
        std::cout << "Fail insert with " << (std::string)mysql_error(&mysql) << std::endl;
        return false;
    }
    std::cout << "Successfully insert " << student.getInfo() << "!" << std::endl;
    return true;
}
bool SqlManager::DeleteMysql(StudentInfo student) {
    std::string sql = "DELETE FROM STUDENT WHERE ";
    sql += "Sno=\'" + student.getSno() + "\' AND ";
    sql += "Sname=\'" + student.getSname() + "\' AND ";
    sql += "Ssex=\'" + student.getSsex() + "\' AND ";
    sql += "Sage=\'" + std::to_string(student.getSage()) + "\' AND ";
    sql += "Sdept=\'" + student.getSdept() + "\'";
    mysql_query(&mysql, "set names utf8");
    if (mysql_query(&mysql, sql.c_str())) {
        std::cout << "Fail delete with " << (std::string)mysql_error(&mysql) << std::endl;
        return false;
    }
    if (!mysql_affected_rows(&mysql)) {
        std::cout << "Fail delete with didn't find student " + student.getInfo() << std::endl;
        return false;
    }
    std::cout << "Successfully delete " << student.getInfo() << "!" << std::endl;
    return true;
}
bool SqlManager::UpdateMysql(StudentInfo student1, StudentInfo student2) {
    std::string sql = "UPDATE STUDENT SET ";
    sql += "Sno=\'" + student2.getSno() + "\',";
    sql += "Sname=\'" + student2.getSname() + "\',";
    sql += "Ssex=\'" + student2.getSsex() + "\',";
    sql += "Sage=\'" + std::to_string(student2.getSage()) + "\',";
    sql += "Sdept=\'" + student2.getSdept() + "\'  WHERE ";
    sql += "Sno=\'" + student1.getSno() + "\' AND ";
    sql += "Sname=\'" + student1.getSname() + "\' AND ";
    sql += "Ssex=\'" + student1.getSsex() + "\' AND ";
    sql += "Sage=\'" + std::to_string(student1.getSage()) + "\' AND ";
    sql += "Sdept=\'" + student1.getSdept() + "\'";
    mysql_query(&mysql, "set names utf8");
    if (mysql_query(&mysql, sql.c_str())) {
        std::cout << "Fail update with " << (std::string)mysql_error(&mysql) << std::endl;
        return false;
    }
    if (!mysql_affected_rows(&mysql)) {
        std::cout << "Fail update with didn't find student " + student1.getInfo() << std::endl;
        return false;
    }
    std::cout << "Successfully update!" << std::endl;
    return true;
}