cmake_minimum_required (VERSION 3.5)
project(commoncpp_test)
INCLUDE_DIRECTORIES(
inc
)
add_definitions("-Wall -llog4cpp -lhiredis")
LINK_DIRECTORIES(
/lib64
)
add_executable(commoncpp_test.a "/root/codes/commoncpp/test/test_01.cpp")
TARGET_LINK_LIBRARIES(commoncpp_test.a commoncpp hiredis log4cpp)

