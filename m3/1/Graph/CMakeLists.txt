project(graphlib)
add_library(graphlib src/ListGraph.cpp
                     src/MatrixGraph.cpp
                     src/SetGraph.cpp
                     src/ArcGraph.cpp)
                     
target_include_directories(graphlib PUBLIC include)