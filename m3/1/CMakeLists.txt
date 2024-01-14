CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
set(CMAKE_CXX_STANDARD 20)
project(Graph)

add_executable(main src/main.cpp)

target_link_libraries(main PUBLIC graphlib)

add_subdirectory(Graph)
include_directories(Graph/include)