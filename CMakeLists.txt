cmake_minimum_required (VERSION 3.5)
project(commoncpp)
INCLUDE_DIRECTORIES(
inc
)
add_definitions("-Wall")
set(lib_hiredis "hiredis")
set(lib_log4cpp "log4cpp")
set(lib_json_c "json-c")
set(lib_pthread "pthread")
link_libraries(${lib_hiredis} ${lib_json_c} ${lib_log4cpp} ) 
add_library(commoncpp SHARED "./src/commonfunction_c.cpp" "./src/log_helper.cpp" "./src/redis_helper.cpp")
TARGET_LINK_LIBRARIES(commoncpp log4cpp hiredis json-c pthread)
INSTALL(FILES inc/commonfunction_c.h inc/redis_helper.h inc/log_helper.h DESTINATION include) 
INSTALL(TARGETS commoncpp LIBRARY DESTINATION  "/lib64")
