cmake_minimum_required(VERSION 3.6)
project(Playin)

set(FREEGLUT_LIBRARIES libfreeglut.a libopengl32.a libglu32.a glew32.lib glew32s.lib -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")

set(SOURCE_FILES src/main.cpp src/common/gui/GuiManager.cpp src/common/gui/GuiManager.h src/common/utils/SafeQueue.cpp src/common/utils/SafeQueue.h src/common/BackgroundWorker.cpp src/common/BackgroundWorker.h src/gui/GuiBase.cpp src/gui/GuiBase.h src/common/utils/events/Event.cpp src/common/utils/events/Event.h src/gui/GuiFrame.cpp src/gui/GuiFrame.h src/common/utils/Vec2d.cpp src/common/utils/Vec2d.h src/common/utils/glutUtils.cpp src/common/utils/glutUtils.h src/common/utils/mathUtils.cpp src/common/utils/mathUtils.h src/gui/GuiWindow.cpp src/gui/GuiWindow.h src/gui/GuiButton.cpp src/gui/GuiButton.h src/gui/GuiFactory.cpp src/gui/GuiFactory.h src/gui/GuiView.cpp src/gui/GuiView.h src/gui/utils/PBOTexture.cpp src/gui/utils/PBOTexture.h src/gui/ProjectionManager.cpp src/gui/ProjectionManager.h src/common/gui/TextureDisplay.cpp src/common/gui/TextureDisplay.h)

link_directories(libs/freeglut/lib/x64)

include_directories(libs/freeglut/include/GL)
include_directories(libs/freeglut/include)

include_directories(src/common)
include_directories(src/common/gui)
include_directories(src/common/utils)
include_directories(src/common/utils/events)

include_directories(src/gui)
include_directories(src/gui/utils)
include_directories(src/gui/resources)

include_directories(src)

add_executable(Playin ${SOURCE_FILES})
target_link_libraries(Playin ${FREEGLUT_LIBRARIES})