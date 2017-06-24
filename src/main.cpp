#include <iostream>
#include <thread>
#include <queue>

#include "glutUtils.h"

#include <stdlib.h>

#define _USE_MATH_DEFINES

#include <gui/GuiManager.h>

using namespace std;

void error_callback(int error, const char *description);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);


void mouse_move_callback(int x, int y);

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

void scroll_callback(GLFWwindow *window, double x, double y);

void renderScene(void);

void resize_callback(int w, int h);

void MouseFunc(int button, int state, int x, int y);

void glutCloseFunc();

void setupProjection(int w, int h);

int main(int argc, char **argv) {

    // Creating window, setting context

    Logger::setLogErrors(true);
    Logger::setLogInfo(true);
    Logger::setLogWarnings(true);
    Logger::setLogStream(std::cout);
    Logger::logFile("log.txt");

    Logger::info("Hello, this is test program!");

    if (!glfwInit()) {
        Logger::info("Init failed!");
        exit(-1);
    }

    glfwSetErrorCallback(error_callback);


    // Window properties
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, constants::opengl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, constants::opengl_version_minor);

    GLFWwindow *window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window) {
        Logger::warning("Failed to create window!");
    }

    glfwMakeContextCurrent(window);

    // Loading OpenGL API
    glewExperimental = GL_TRUE;
    GLenum glewinit = glewInit();
    if (glewinit != GLEW_OK) {
        Logger::error("Glew init error code: ", glewinit);
        exit(-1);
    } else {
        Logger::info("Glut init success!");
    }

    // Registering callbacks

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Running main loop


    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    //glClearColor((float)xpos/1000.0,(float)ypos/1000.0,0,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 1, 0, 1, -1);

    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_LIGHTING);

    glDisable(GL_SCISSOR_TEST);

    Vec2d old_mouse_pos;
    Vec2d mouse_pos;
    Vec2i old_screen_size;
    Vec2i screen_size;

    //ShaderLoader::Init();

    GuiManager::Init();

    //bg_thread = thread(run_background_thread);

    glfwGetFramebufferSize(window, &screen_size.x, &screen_size.y);
    setupProjection(screen_size.x, screen_size.y);
    old_screen_size = screen_size;

    GuiManager::PostInit();

    GuiManager::OnResize(ProjectionManager::getViewportObjSize());

    Logger::info("Running main loop!");

    while (!glfwWindowShouldClose(window)) {

        glfwWaitEventsTimeout(0.001);

        glfwGetFramebufferSize(window, &screen_size.x, &screen_size.y);
        glfwGetCursorPos(window, &mouse_pos.x, &mouse_pos.y);

        if (screen_size.x != old_screen_size.x || screen_size.y != old_screen_size.y) {
            resize_callback(screen_size.x, screen_size.y);
            old_screen_size = screen_size;
        }

        if (mouse_pos.x != old_mouse_pos.x || mouse_pos.y != old_mouse_pos.y) {
            mouse_move_callback((int) mouse_pos.x, (int) mouse_pos.y);
            old_mouse_pos = mouse_pos;
        }

        //glfwPollEvents();

        renderScene();
        //VBOTest::Drawrect(Vec2d(0, 0), Vec2d(2, 2));

        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(0);
}

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_move_callback(int x, int y) {

    Vec2d local_mpos = ProjectionManager::unProjectMouse( Vec2i(x,y) );

    GuiManager::OnMouseMove(local_mpos);

}

void renderScene(void) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_SCISSOR_TEST);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    GuiManager::draw();

    glFlush();
}

void setupProjection(int w, int h) {
    if (h == 0)
        h = 1;

    Vec2i size_i{w, h};

    ProjectionManager::setScreenSize(size_i);
    //ProjectionManager::setScale(Vec2d(0.5,0.5));
    ProjectionManager::setViewportProjection(Vec2i::ZERO,size_i);
}

void resize_callback(int w, int h) {

    setupProjection(w,h);

    GuiManager::OnResize(ProjectionManager::getViewportObjSize());

}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {

    double x;
    double y;

    glfwGetCursorPos(window, &x, &y);

    Vec2d local_mpos = ProjectionManager::unProjectMouse(Vec2i((int) x, (int) y));

    GuiManager::OnMouseDown(button, action, local_mpos);

}

void scroll_callback(GLFWwindow *window, double x, double y) {

    GuiManager::OnScroll(Vec2d(x, y));

}