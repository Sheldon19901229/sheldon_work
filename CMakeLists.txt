cmake_minimum_required(VERSION 3.24)
project(LearnCpp-01 LANGUAGES CXX)

include_directories(learn_stl)
include_directories(Sort)
include_directories(Log)
include_directories(Interview_code/LeeCode)

link_directories(learn_stl)
link_directories(sort)
link_directories(Interview_code/LeeCode)

add_subdirectory(learn_stl)
add_subdirectory(sort)
add_subdirectory(Interview_code/LeeCode)

add_executable(LearnCpp main.cpp)
target_link_libraries(LearnCpp learnstl learnsort leecode)