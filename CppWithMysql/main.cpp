# include <bits/stdc++.h>
# include "include/SqlManager.h"
# include "include/StudentInfo.h"

int main () {
    SqlManager sqm;
    sqm.ConnectMysql();
    sqm.QueryMysql("SELECT * FROM STUDENT");
    StudentInfo student1 = {"1010101", "张三", "男", 21, "计算机系"};
    StudentInfo student2 = {"1010101", "张三", "男", 23, "计算机系"};
    //if (!sqm.InsertMysql(student1)) return 0;
    //if (!sqm.DeleteMysql(student1)) return 0;
    //if (!sqm.UpdateMysql(student1, student2)) return 0;
    sqm.QueryMysql("SELECT * FROM STUDENT");
    return 0;
}
