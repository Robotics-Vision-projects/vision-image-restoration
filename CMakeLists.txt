# CMake version.
cmake_minimum_required(VERSION 2.8.11)

# The name of the project.
project(vision_image_restoration)

# Used to resolve absolute path names
SET(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

# Use c++11 and check OpenCV 3.
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
find_package(OpenCV 3 REQUIRED)

# Add the source files to build.
add_executable(vision_image_restoration src/vision_image_restoration.cpp)
target_link_libraries(vision_image_restoration ${OpenCV_LIBS})

MESSAGE(${PROJECT_NAME} " done!")
