cmake_minimum_required(VERSION 3.24)
project(LearnCpp-01 LANGUAGES CXX)

include_directories(LearnStl)
link_directories(LearnStl)

add_subdirectory(LearnStl)

add_executable(LearnCpp main.cpp)
target_link_libraries(LearnCpp learnstl)