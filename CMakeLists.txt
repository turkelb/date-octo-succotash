cmake_minimum_required(VERSION 3.12) 
project(date)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_executable(date src/main.cpp src/date.cpp)
