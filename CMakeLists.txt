cmake_minimum_required(VERSION 3.6)
project(Playin)

set(FREEGLUT_LIBRARIES libopengl32.a libglu32.a glew32.lib glew32s.lib libglfw3.a -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11 -m64")

set(SOURCE_FILES src/main.cpp src/common/gui/GuiManager.cpp src/common/gui/GuiManager.h src/common/utils/SafeQueue.cpp src/common/utils/SafeQueue.h src/common/BackgroundWorker.cpp src/common/BackgroundWorker.h src/gui/utils/GuiBase.cpp src/gui/utils/GuiBase.h src/common/utils/events/Event.cpp src/common/utils/events/Event.h src/gui/GuiFrame.cpp src/gui/GuiFrame.h src/common/utils/Vec2d.cpp src/common/utils/Vec2d.h src/common/utils/glutUtils.cpp src/common/utils/glutUtils.h src/common/utils/mathUtils.cpp src/common/utils/mathUtils.h src/gui/GuiWindow.cpp src/gui/GuiWindow.h src/gui/GuiButton.cpp src/gui/GuiButton.h src/gui/utils/GuiFactory.cpp src/gui/utils/GuiFactory.h src/gui/GuiView.cpp src/gui/GuiView.h src/gui/utils/PBOTexture.cpp src/gui/utils/PBOTexture.h src/gui/utils/ProjectionManager.cpp src/gui/utils/ProjectionManager.h src/common/gui/GuiTextureView.cpp src/common/gui/GuiTextureView.h src/gui/utils/FBTexture.cpp src/gui/utils/FBTexture.h src/gui/utils/AttributeStack.cpp src/gui/utils/AttributeStack.h)

include_directories(libs/glfw/include/GLFW)
include_directories(libs/glew/include)

link_directories(libs/glew/lib)
link_directories(libs/glfw/lib)

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