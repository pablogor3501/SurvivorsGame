cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 17)

project(SurvivorsGame)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})