cmake_minimum_required(VERSION 3.24)
project(LearnCpp-01 LANGUAGES CXX)

include_directories(LearnStl)
include_directories(Sort)
include_directories(Log)
include_directories(InterviewCode/LeeCode)

link_directories(LearnStl)
link_directories(Sort)
link_directories(Log)
link_directories(InterviewCode/LeeCode)

add_subdirectory(LearnStl)
add_subdirectory(Sort)
add_subdirectory(Log)
add_subdirectory(InterviewCode/LeeCode)

add_executable(LearnCpp main.cpp)
target_link_libraries(LearnCpp learnstl learnsort log leecode)