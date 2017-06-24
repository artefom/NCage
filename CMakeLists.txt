cmake_minimum_required(VERSION 3.8)
project(Playin)

set(FREEGLUT_LIBRARIES libopengl32.a libglu32.a libglew32.dll.a libglfw3.a -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11 -m64")

set(SOURCE_FILES src/main.cpp src/common/gui/GuiManager.cpp src/common/gui/GuiManager.h src/common/utils/SafeQueue.cpp src/common/utils/SafeQueue.h src/common/BackgroundWorker.cpp src/common/BackgroundWorker.h src/gui/utils/GuiBase.cpp src/gui/utils/GuiBase.h src/common/utils/events/Event.cpp src/common/utils/events/Event.h src/gui/GuiFrame.cpp src/gui/GuiFrame.h src/common/utils/Vec2d.cpp src/common/utils/Vec2d.h src/common/utils/glutUtils.cpp src/common/utils/glutUtils.h src/common/utils/mathUtils.cpp src/common/utils/mathUtils.h src/gui/GuiWindow.cpp src/gui/GuiWindow.h src/gui/GuiButton.cpp src/gui/GuiButton.h src/gui/utils/GuiFactory.cpp src/gui/utils/GuiFactory.h src/gui/GuiView.cpp src/gui/GuiView.h src/gui/utils/PBOTexture.cpp src/gui/utils/PBOTexture.h src/gui/utils/ProjectionManager.cpp src/gui/utils/ProjectionManager.h src/common/gui/GuiTextureView.cpp src/common/gui/GuiTextureView.h src/gui/utils/FBTexture.cpp src/gui/utils/FBTexture.h src/gui/utils/AttributeStack.cpp src/gui/utils/AttributeStack.h src/common/Logger.cpp src/common/Logger.h src/gui/VBOTest/VBOTest.cpp src/gui/VBOTest/VBOTest.h src/gui/VBOTest/VBOMesh.cpp src/gui/VBOTest/VBOMesh.h src/test/test.cpp src/gui/render/RenderPrimitive.cpp src/gui/render/RenderPrimitive.h src/gui/render/Vertex.cpp src/gui/render/Vertex.h src/gui/render/ShaderLoader.cpp src/gui/render/ShaderLoader.h src/common/utils/FileIO.cpp src/common/utils/FileIO.h src/gui/render/RenderManager.cpp src/gui/render/RenderManager.h)

set(TEST_DIR src/test)
set(TEST_FILES ${TEST_DIR}/test.cpp src/test/unit_test.h)

include_directories(libs/glfw/include/GLFW)
include_directories(libs/glew/include)
include_directories(libs/UnitTests)

link_directories(libs/glew/lib)
link_directories(libs/glfw/lib)

include_directories(src/common)
include_directories(src/common/gui)
include_directories(src/common/utils)
include_directories(src/common/utils/events)

include_directories(src/gui)
include_directories(src/gui/render)
include_directories(src/gui/utils)
include_directories(src/gui/resources)

include_directories(src)

file(COPY "res" DESTINATION "${CMAKE_BINARY_DIR}")

#add_custom_target(copy_shaders ALL
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "${CMAKE_SOURCE_DIR}/res" "$<TARGET_FILE_DIR:Playin>/res"
#        COMMENT "Copy shaders to build tree"
#        VERBATIM)
#
#add_custom_target(copy_shaders_test ALL
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "${CMAKE_SOURCE_DIR}/res" "$<TARGET_FILE_DIR:Playin_test>/res"
#        COMMENT "Copy shaders to build tree"
#        VERBATIM)


set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.64.0 COMPONENTS unit_test_framework REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    add_executable(Playin_test ${TEST_FILES})
    add_executable(Playin ${SOURCE_FILES})

    target_link_libraries(Playin ${FREEGLUT_LIBRARIES})
    target_link_libraries(Playin ${Boost_LIBRARIES})
    target_link_libraries(Playin_test ${Boost_LIBRARIES})

    add_custom_command(TARGET Playin POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/dlls"
            $<TARGET_FILE_DIR:Playin>)
endif ()
