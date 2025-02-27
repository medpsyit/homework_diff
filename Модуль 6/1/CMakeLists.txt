cmake_minimum_required(VERSION 3.20)
project(testBD)
set(CMAKE_CXX_STANDARD 20)

set(PostgreSQL_ADDITIONAL_VERSIONS "17" "17.2")

find_package(PostgreSQL REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

set (HEADERS 
"include/client.h" 
"include/number.h" 
"include/interface.h"
)

set (SOURCES 
"src/client.cpp" 
"src/number.cpp" 
"src/interface.cpp" 
"main.cpp" 
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL libpqxx::pqxx)