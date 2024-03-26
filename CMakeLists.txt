cmake_minimum_required(VERSION 3.0)
project(HW2)
set(CMAKE_CXX_STANDARD 20)

include_directories(Homework2/include)
add_executable(HW2 main.cpp question1.cpp question2.cpp Sensor-Factory-ctrlSys.cpp Robot-Tools.cpp
                question3.cpp Pilot-ATC.cpp)

find_package(Threads)
target_link_libraries(HW2 Threads::Threads)