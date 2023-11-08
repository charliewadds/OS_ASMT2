cmake_minimum_required(VERSION 3.23)
project(OS_ASMT2 C)

set(CMAKE_C_STANDARD 99)

add_library(OS_ASMT2 src/utils.c)

target_sources(OS_ASMT2 PRIVATE src/dataTypes/ProcLL.c)
# Create an executable for testing the library
add_executable(testMain tests/testMain.c)

# Link the library to the testMain executable
target_link_libraries(testMain PRIVATE OS_ASMT2)