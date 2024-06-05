cmake_minimum_required(VERSION 3.10)
project(data_structures)



add_library(structures_lib INTERFACE)
target_include_directories(structures_lib INTERFACE include/)

add_executable(test_structures
        src/test_structures.cpp)
target_link_libraries(test_structures structures_lib)

add_executable(efficiency_experiments
        src/main.cpp)
target_link_libraries(efficiency_experiments structures_lib)

