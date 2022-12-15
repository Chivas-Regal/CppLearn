#ifndef CPPWITHMYSQL_STUDENTINFO_H
#define CPPWITHMYSQL_STUDENTINFO_H

# include <bits/stdc++.h>

class StudentInfo {
private:
    std::string Sno;
    std::string Sname;
    std::string Ssex;
    int Sage;
    std::string Sdept;
public:
    StudentInfo();
    StudentInfo(const std::string &sno,
                const std::string &sname,
                const std::string &ssex,
                const int &sage,
                const std::string &sdept);
    std::string getSno ();
    std::string getSname ();
    std::string getSsex ();
    int getSage ();
    std::string getSdept ();
    std::string getInfo ();
};

#endif //CPPWITHMYSQL_STUDENTINFO_H
