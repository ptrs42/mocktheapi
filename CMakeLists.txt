cmake_minimum_required(VERSION 3.24)
project(mocktheapi)

set(CMAKE_CXX_STANDARD 17)

add_executable(mocktheapi main.cpp Request.cpp Request.h Response.cpp Response.h RequestResponse.cpp RequestResponse.h RequestResponseJsonSerializer.cpp RequestResponseJsonSerializer.h)

FIND_PACKAGE(Boost COMPONENTS program_options filesystem json REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(mocktheapi ${Boost_LIBRARIES})