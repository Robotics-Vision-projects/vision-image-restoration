# CMake version.
cmake_minimum_required(VERSION 2.8.11)

# The name of the project.
project(vision_image_restoration)

# Used to resolve absolute path names
set(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${CMAKE_SOURCE_DIR}/include")

# Use c++11 and check OpenCV 3.
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
find_package(OpenCV 3 REQUIRED)

set(SOURCEFILES src/vision_image_restoration.cpp src/tools.cpp include/tools.h)
set(IM1_SOURCEFILES src/img1.cpp src/tools.cpp include/tools.h
	src/filters.cpp include/filters.h)

add_executable(vision_image_restoration ${SOURCEFILES})
add_executable(image1 ${IM1_SOURCEFILES})

target_link_libraries(vision_image_restoration ${OpenCV_LIBS})
target_link_libraries(image1 ${OpenCV_LIBS})

message(${PROJECT_NAME} " done!")
