# include <bits/stdc++.h>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
# include "include/SqlManager.h"
# include "include/StudentInfo.h"

void Header ();
int Ender ();

void showAll (SqlManager &sqm);
void showQuery (SqlManager &sqm, cgicc::form_iterator fit_name, cgicc::form_iterator fit_no, cgicc::form_iterator fit_sex, cgicc::form_iterator fit_age, cgicc::form_iterator fit_dept);

void delRow (SqlManager &sqm, int lineidx);
void addRow (SqlManager &sqm, cgicc::form_iterator fit_sno, cgicc::form_iterator fit_sname, cgicc::form_iterator fit_sex, cgicc::form_iterator fit_age, cgicc::form_iterator fit_dept);

int main () {
    Header();

    // 获取好上一个自己传递过来的数据
    cgicc::Cgicc formData;
    cgicc::form_iterator fit_name = formData.getElement("sname");
    cgicc::form_iterator fit_no = formData.getElement("sno");
    cgicc::form_iterator fit_sex = formData.getElement("ssex");
    cgicc::form_iterator fit_age = formData.getElement("sage");
    cgicc::form_iterator fit_dept = formData.getElement("sdept");
    cgicc::form_iterator fit_addsno = formData.getElement("add_no");
    cgicc::form_iterator fit_addsname = formData.getElement("add_name");
    cgicc::form_iterator fit_addsex = formData.getElement("add_sex");
    cgicc::form_iterator fit_addage = formData.getElement("add_age");
    cgicc::form_iterator fit_adddept = formData.getElement("add_dept");

    SqlManager sqm;
    sqm.ConnectMysql();
    sqm.QueryMysql("SELECT * FROM STUDENT");

    // 删除
    for (int i = 1; i <= sqm.numRow(); i ++) {
        if (!formData.getElement("delbtn" + std::to_string(i))->isEmpty()) {
            delRow(sqm, i);
            break;
        }
    }
    // 添加
    addRow(sqm, fit_addsno, fit_addsname, fit_addsex, fit_addage, fit_adddept);

    // 制作表格
    std::cout << "        <table>\n";
    if (fit_name->isEmpty() && fit_no->isEmpty() && fit_sex->isEmpty() && fit_age->isEmpty() && fit_dept->isEmpty()) {
        showAll(sqm);
    } else {
        showQuery(sqm, fit_name, fit_no, fit_sex, fit_age, fit_dept);
    }
    // 向下一个自己传递的添加的信息
    std::cout << "          <tr>\n";
    std::cout << "              <td><input type='text' name='add_no'/></td>\n";
    std::cout << "              <td><input type='text' name='add_name'/></td>\n";
    std::cout << "              <td><input type='text' name='add_sex'/></td>\n";
    std::cout << "              <td><input type='text' name='add_age'/></td>\n";
    std::cout << "              <td><input type='text' name='add_dept'/></td>\n";
    std::cout << "              <td><input type='submit' value='+'/></td>\n";
    std::cout << "          </tr>\n";
    std::cout << "        </table>\n";

    return Ender();
}

void Header () {
    std::cout << "Content-Type:text/html;charset=utf-8\r\n\r\n\r\n";
    std::string html = "<!DOCTYPE html>\n"
                       "<html lang='en' style='height: 100%'>\n"
                       "<head>\n"
                       "    <meta charset=\"utf-8\">\n"
                       "    <title>数据库</title>\n"
                       "    <style>\n"
                       "        *{\n"
                       "            margin: 0;\n"
                       "            padding: 0;\n"
                       "        }\n"
                       "        .tab {\n"
                       "            position: absolute;\n"
                       "            width: calc(100% - 20px);\n"
                       "            height: 60px;\n"
                       "            background-color: white;\n"
                       "            color: black;\n"
                       "            text-align: left;\n"
                       "            padding: 10px;\n"
                       "            box-shadow: 0px 0px 10px 5px #aaa;\n"
                       "            z-index: 2;\n"
                       "        }\n"
                       "        .leftSize {\n"
                       "            position: absolute;\n"
                       "            margin-top: 80px;\n"
                       "            background-color: black;\n"
                       "            color: white;\n"
                       "            float: left;\n"
                       "            height: calc(100% - 80px);\n"
                       "            width: 30%;\n"
                       "            text-align: center;\n"
                       "            z-index: 2;\n"
                       "        }\n"
                       "        .main {\n"
                       "            position: absolute;\n"
                       "            margin-top: 80px;\n"
                       "            margin-left: 30%;\n"
                       "            height: calc(100% - 80px);\n"
                       "            width: 70%;\n"
                       "            background-color: #F0F0F0;\n"
                       "            text-align: center;\n"
                       "        }\n"
                       "        table {\n"
                       "            background-color: white;\n"
                       "            width: 70%;\n"
                       "            margin-left: 15%;\n"
                       "            border-radius: 20px;\n"
                       "            box-shadow: 0px 0px 10px 5px #e5e5e5;\n"
                       "        }\n"
                       "        tr, td {\n"
                       "            border-top: 1px solid #dddddd;\n"
                       "            color: black;\n"
                       "        }\n"
                       "    </style>\n"
                       "</head>\n"
                       "<body style='height: 100%; width: 100%;'>\n"
                       "<form  action=\"./CppWithMysql.cgi\" method=\"POST\" target=\"_blank\"  style='height: 100%; width: 100%;'>\n"
                       "    <div class=\"tab\"><h1>学生信息收集</h1></div>\n"
                       "    <!--搜索栏-->\n"
                       "    <div class=\"leftSize\">\n"
                       "            姓名：<input type='text' name='sname' style=\"margin-top: 20px;\"/></br>\n"
                       "            学号：<input type='text' name='sno'/></br>\n"
                       "            性别：<input type='text' name='ssex'/></br>\n"
                       "            年龄：<input type='text' name='sage'/></br>\n"
                       "            系别：<input type='text' name='sdept'/></br>\n"
                       "            </br></br>\n"
                       "            <div style='text-align: center'>\n"
                       "                <input type='submit' value='搜索'/>\n"
                       "            </div>\n"
                       "    </div>\n"
                       "        <div class=\"main\">\n"
                       "        <br><br><br>\n"
                       "        <h2 style=\"margin-left: 10px;\">学生信息表：</h2>\n"
                       "        <br><br>";
    std::cout << html << std::endl;

}

int Ender () {
    std::cout << "</form></body></html>";
    return 0;
}

void showQuery (SqlManager &sqm, cgicc::form_iterator fit_name, cgicc::form_iterator fit_no, cgicc::form_iterator fit_sex, cgicc::form_iterator fit_age, cgicc::form_iterator fit_dept) {
    std::string sql = "SELECT * FROM STUDENT WHERE";
    if (!fit_no->isEmpty()) sql += " Sno=\"" + **fit_no + "\" AND";
    if (!fit_name->isEmpty()) sql += " Sname=\"" + **fit_name + "\" AND";
    if (!fit_sex->isEmpty()) sql += " Ssex=\"" + **fit_sex + "\" AND";
    if (!fit_age->isEmpty()) sql += " Sage=" + **fit_age + " AND";
    if (!fit_dept->isEmpty()) sql += " Sdept=\"" + **fit_dept + "\" AND";
    sql.pop_back(); sql.pop_back(); sql.pop_back();
    sqm.QueryMysql(sql);
    std::vector<std::vector<std::string> > output = sqm.OutputMysql();
    int lineidx = 1;
    for (const std::vector<std::string> &line : output) {
        std::cout << "          <tr>\n";
        if (line[0] == "Sno") {
            std::cout << "              <th>学号</th>\n";
            std::cout << "              <th>姓名</th>\n";
            std::cout << "              <th>性别</th>\n";
            std::cout << "              <th>年龄</th>\n";
            std::cout << "              <th>系别</th>\n";
            std::cout << "              <th>操作</th>\n";
        } else {
            for (const std::string &curcol : line) {
                std::cout << "            <td>" << curcol << "</td>\n";
            }
            std::cout << "              <td><button type=\"submit\" name=\"delbtn" << std::to_string(lineidx) << "\" value=\"" << std::to_string(lineidx) << "\">-</button></td>\n";
            lineidx ++;
        }
        std::cout << "          </tr>\n";
    }
}
void showAll (SqlManager &sqm) {
    sqm.QueryMysql("SELECT * FROM STUDENT");
    std::vector<std::vector<std::string> > output = sqm.OutputMysql();
    int lineidx = 1;
    for (const std::vector<std::string> &line : output) {
        std::cout << "          <tr>\n";
        if (line[0] == "Sno") {
            std::cout << "              <th>学号</th>\n";
            std::cout << "              <th>姓名</th>\n";
            std::cout << "              <th>性别</th>\n";
            std::cout << "              <th>年龄</th>\n";
            std::cout << "              <th>系别</th>\n";
            std::cout << "              <th>操作</th>\n";
        } else {
            for (const std::string &curcol : line) {
                std::cout << "              <td>" << curcol << "</td>\n";
            }
            std::cout << "              <td><button type=\"submit\" name=\"delbtn" << std::to_string(lineidx) << "\" value=\"" << std::to_string(lineidx) << "\">-</button></td>\n";
            lineidx ++;
        }
        std::cout << "          </tr>\n";
    }
}

void delRow (SqlManager &sqm, int lineidx) {
    std::vector<std::vector<std::string> > table = sqm.OutputMysql();
    StudentInfo stu(table[lineidx][0], table[lineidx][1], table[lineidx][2], std::stoi(table[lineidx][3]), table[lineidx][4]);
    sqm.DeleteMysql(stu);
}

void addRow (SqlManager &sqm, cgicc::form_iterator fit_sno, cgicc::form_iterator fit_sname, cgicc::form_iterator fit_sex, cgicc::form_iterator fit_age, cgicc::form_iterator fit_dept) {
    if (fit_sno->isEmpty()) return;
    if (fit_sname->isEmpty()) return;
    if (fit_sex->isEmpty()) return;
    if (fit_age->isEmpty()) return;
    if (fit_dept->isEmpty()) return;
    StudentInfo stu(**fit_sno, **fit_sname, **fit_sex, std::stoi(**fit_age), **fit_dept);
    sqm.InsertMysql(stu);
}


// to /opt/homebrew/var/www/cgi-bin/cppwithmysql/CppWithMysql.cgi