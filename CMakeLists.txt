cmake_minimum_required(VERSION 3.24)
project(LearnCpp-01 LANGUAGES CXX)

include_directories(LearnStl)
include_directories(Sort)

link_directories(LearnStl)
link_directories(Sort)

add_subdirectory(LearnStl)
add_subdirectory(Sort)

add_executable(LearnCpp main.cpp)
target_link_libraries(LearnCpp learnstl learnsort)