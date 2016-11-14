cmake_minimum_required(VERSION 3.6)
project(Jaimin___CSCI_561_Homework_3_Solution)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

set(SOURCE_FILES main.cc)
add_executable(Jaimin___CSCI_561_Homework_3_Solution ${SOURCE_FILES})

target_link_libraries(Jaimin___CSCI_561_Homework_3_Solution homework3)