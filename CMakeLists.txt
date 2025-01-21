cmake_minimum_required(VERSION 3.30)
project(ppp_c3)

set(CMAKE_CXX_STANDARD 26)


find_package(TagLib REQUIRED)

add_executable(ppp_c3 main.cpp)
add_executable(ppp_c3i main_extra.cpp
)
add_executable(ppp_c3ii main_calc.cpp)
add_executable(ppp_c3iii main_greeter.cpp)

target_link_libraries(ppp_c3i
        TagLib::tag
)
