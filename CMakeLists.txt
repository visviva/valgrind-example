cmake_minimum_required(VERSION 3.16)
project(Valgrind_example)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(sort sort.cpp)

if(DEFINED DISABLE_FORTIFY_SOURCE)
	target_compile_options(sort PRIVATE -fno-stack-protector -D_FORTIFY_SOURCE=0)
endif()

target_compile_options(sort PRIVATE -Wall -Wextra -std=c++17 -O0 -ggdb)