cmake_minimum_required(VERSION 3.6)
project(Playin)

set(FREEGLUT_LIBRARIES libfreeglut.a libopengl32.a libglu32.a glew32.lib glew32s.lib -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")

set(SOURCE_FILES src/main.cpp src/GuiManager.cpp src/GuiManager.h src/utils/SafeQueue.cpp src/utils/SafeQueue.h src/BackgroundWorker.cpp src/BackgroundWorker.h src/gui/GuiBase.cpp src/gui/GuiBase.h src/events/Event.cpp src/events/Event.h src/gui/GuiFrame.cpp src/gui/GuiFrame.h src/utils/Vec2d.cpp src/utils/Vec2d.h src/utils/glutUtils.cpp src/utils/glutUtils.h src/utils/mathUtils.cpp src/utils/mathUtils.h src/gui/GuiWindow.cpp src/gui/GuiWindow.h src/gui/GuiButton.cpp src/gui/GuiButton.h src/gui/GuiFactory.cpp src/gui/GuiFactory.h src/gui/GuiView.cpp src/gui/GuiView.h src/gui/utils/PBOTexture.cpp src/gui/utils/PBOTexture.h src/gui/ProjectionManager.cpp src/gui/ProjectionManager.h)

link_directories(libs/freeglut/lib/x64)

include_directories(libs/freeglut/include/GL)
include_directories(libs/freeglut/include)
include_directories(src/events)
include_directories(src/gui)
include_directories(src/gui/utils)
include_directories(src/resources)
include_directories(src/utils)
include_directories(src)

add_executable(Playin ${SOURCE_FILES})
target_link_libraries(Playin ${FREEGLUT_LIBRARIES})