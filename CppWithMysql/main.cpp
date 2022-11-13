# include <bits/stdc++.h>
# include "include/SqlManager.h"
# include "include/StudentInfo.h"

int main () {
    SqlManager sqm;
    sqm.ConnectMysql();
    sqm.QueryMysql("SELECT * FROM STUDENT");
    StudentInfo student = {"1010101", "张磊", "男", 21, "计算机系"};
    StudentInfo student2 = {"1010101", "张磊", "男", 23, "计算机系"};
    if (!sqm.DeleteMysql(student2)) return 0;
    sqm.QueryMysql("SELECT * FROM STUDENT");
    return 0;
}
