cmake_minimum_required(VERSION 3.26)
project(opencv)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

message(STATUS "donwloadign opencv")

#FetchContent_Declare(
#        opencv
#        GIT_REPOSITORY https://github.com/opencv/opencv.git
#        GIT_TAG        4.4.0
#)
#FetchContent_GetProperties(opencv)
#if (NOT opencv_POPULATED)
#    FetchContent_Populate(opencv)
#endif ()
#FetchContent_MakeAvailable(opencv)

# Find on pc
set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(OpenCV REQUIRED)

# Header
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Define Marco
#target_compile_definitions(${PROJECT_NAME} PRIVATE ASSERTS="assets/")
add_compile_definitions(${PROJECT_NAME} PRIVATE ASSERTS="${CMAKE_SOURCE_DIR}/assets")
add_compile_definitions(${PROJECT_NAME} PRIVATE MODULES="${CMAKE_SOURCE_DIR}/module")
add_compile_definitions(${PROJECT_NAME} PRIVATE DIST="${CMAKE_SOURCE_DIR}/dist")
# Link
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
