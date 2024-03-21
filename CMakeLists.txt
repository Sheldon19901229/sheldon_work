cmake_minimum_required(VERSION 3.20)
project(LearnCpp-01 LANGUAGES CXX)

include_directories(learn_stl)
include_directories(Sort)
include_directories(Log)
include_directories(interview_code/LeeCode)

link_directories(learn_stl)
link_directories(Sort)
link_directories(interview_code/LeeCode)

add_subdirectory(learn_stl)
add_subdirectory(Sort)
add_subdirectory(interview_code/LeeCode)

add_executable(LearnCpp main.cpp)
target_link_libraries(LearnCpp learnstl learnsort leecode)