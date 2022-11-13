cmake_minimum_required(VERSION 3.20)
project(CppWithMysql)

include_directories("/usr/local/mysql-8.0.26-macos11-arm64/include")
link_directories("/usr/local/mysql-8.0.26-macos11-arm64/lib")

set(CMAKE_CXX_STANDARD 14)

add_executable(CppWithMysql main.cpp include/SqlManager.cpp include/SqlManager.h include/StudentInfo.h include/StudentInfo.cpp)
target_link_libraries(CppWithMysql libmysqlclient.dylib)