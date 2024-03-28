ccmake_minimum_required(VERSION 3.5)
project(HW2)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

# Dependencies
find_package(OpenGL REQUIRED)
find_package(Threads)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
)
FetchContent_MakeAvailable(glew)

# Our Project
set(SOURCES_FILES
    src/main.cpp
    src/question1.cpp
    src/question2.cpp
    src/question3.cpp
    src/question4.cpp
    src/Pilot-ATC.cpp
    src/Robot-Tools.cpp
    src/Sensor-Factory-ctrlSys.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw libglew_static Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
