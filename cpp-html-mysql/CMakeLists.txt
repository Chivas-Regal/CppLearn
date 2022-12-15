cmake_minimum_required(VERSION 3.20)
project(cpp-html-mysql)

include_directories("/usr/local/mysql-8.0.26-macos11-arm64/include")
include_directories("/usr/local/include")
link_directories("/usr/local/mysql-8.0.26-macos11-arm64/lib")
link_directories("/usr/local/lib")

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_CXX_FLAGS "-std=c++11 -lcgicc")

add_executable(CppWithMysql.cgi main.cpp include/SqlManager.cpp include/SqlManager.h include/StudentInfo.h include/StudentInfo.cpp)
target_link_libraries(CppWithMysql.cgi libmysqlclient.dylib)
target_link_libraries(CppWithMysql.cgi libcgicc.dylib)