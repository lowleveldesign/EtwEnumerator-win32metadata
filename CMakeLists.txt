cmake_minimum_required(VERSION 3.18)

project(wtrace VERSION 4.0.0.0)

add_compile_definitions(UNICODE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4 -WX")

add_subdirectory(src)
