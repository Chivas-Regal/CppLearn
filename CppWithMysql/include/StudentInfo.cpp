# include "StudentInfo.h"

StudentInfo::StudentInfo() {
    Sno = "0000000";
    Sname = "空白";
    Ssex = "空";
    Sage = 0;
    Sdept = "空白系";
}
StudentInfo::StudentInfo(const std::string &sno,
                         const std::string &sname,
                         const std::string &ssex,
                         const int &sage,
                         const std::string &sdept):Sno(sno),Sname(sname),Ssex(ssex),Sage(sage),Sdept(sdept) {
    std::cout << "Successfully create student with " << sno << " " << sname << " " << ssex << " " << sage << " " << sdept << std::endl;
}

int StudentInfo::getSage() {return Sage;}
std::string StudentInfo::getSdept() {return Sdept;}
std::string StudentInfo::getSname() {return Sname;}
std::string StudentInfo::getSno() {return Sno;}
std::string StudentInfo::getSsex() {return Ssex;}
std::string StudentInfo::getInfo() {
    return "(" + Sno + "," + Sname + "," + Ssex + "," + std::to_string(Sage) + "," + Sdept + ")";
}