cmake_minimum_required(VERSION 3.6)
project(Playin)

set(FREEGLUT_LIBRARIES libfreeglut.a libopengl32.a libglu32.a)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")

set(SOURCE_FILES src/main.cpp src/GuiManager.cpp src/GuiManager.h src/utils/thread_factory.cpp src/utils/thread_factory.h)

link_directories(libs/freeglut/lib/x64)

include_directories(libs/freeglut/include/GL)
include_directories(libs/freeglut/include)
include_directories(src/resources)
include_directories(src)

add_executable(Playin ${SOURCE_FILES})
target_link_libraries(Playin ${FREEGLUT_LIBRARIES})