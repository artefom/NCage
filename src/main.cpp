#define DEBUG

#include <iostream>
#include <thread>
#include <queue>
#include <glutUtils.h>
#include <mathUtils.h>

#define bg(x) cout << string("BG: ")+string(x)+string("\n");
#define gui(x) cout << string("GUI: ")+string(x)+string("\n");


#include "resources/constants.h"
#include "SafeQueue.h"
#include "BackgroundWorker.h"
#include "GuiManager.h"
#include "PBOTexture.h"
#include "ProjectionManager.h"

using namespace std;

void PassiveMouseMove(int x, int y);

void renderScene(void);

void resize(int w, int h);

void MouseFunc(int button, int state, int x, int y);

void glutCloseFunc();

void setupProjection(int w, int h);

bool shouldExit = false;

thread bg_thread;

int main(int argc, cstring argv[]) {

    glutInit(&argc, argv);

    Vec2i window_size = Vec2i(512,512);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window_size.x, window_size.y);

    glClearColor(0.0,0.0,0.0,0.0);

    //glEnable(GL_SCISSOR_TEST);
    glShadeModel(GL_FLAT);                      // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    glDisable(GL_LIGHTING);

    glutCreateWindow("Ass class destroyer");

    GLenum glewinit = glewInit();
    if (glewinit != GLEW_OK) {
        std::cout << "Glew not okay! " << glewinit;
        exit(-1);
    }

    gui("Registerring mouse callbacks");

    glutDisplayFunc(renderScene);

    glutPassiveMotionFunc(PassiveMouseMove);
    glutMotionFunc(PassiveMouseMove);
    glutMouseFunc(MouseFunc);

    glutReshapeFunc(resize);
    glutIdleFunc(renderScene);
    glutCloseFunc(glutCloseFunc);

    GuiManager::Init();

    bg_thread = thread(run_background_thread);

    setupProjection(window_size.x,window_size.y);

    GuiManager::PostInit();

    glutMainLoop();

    return 0;
}

void glutCloseFunc() {

    BackgroundWorker::input_events.enqueue(-1);
    bg_thread.join();

    GuiManager::terminate();

}

void PassiveMouseMove(int x, int y) {

    Vec2d local_mpos = ProjectionManager::unProjectMouse( Vec2i(x,y) );

    GuiManager::OnMouseMove(local_mpos);

}

void renderScene(void) {

    // Clear all

    glClear(GL_COLOR_BUFFER_BIT);

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE);

    GuiManager::draw();

    glutPostRedisplay();
    glFlush();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void setupProjection(int w, int h) {
    if (h == 0)
        h = 1;

    Vec2i size_i{(Vec2i::ctype)w,(Vec2i::ctype)h};
    Vec2d size_d{(Vec2d::ctype)w,(Vec2d::ctype)h};

    ProjectionManager::setScreenSize(size_i);
    //ProjectionManager::setScale(Vec2d(0.5,0.5));
    //ProjectionManager::setScreenSize(Vec2d(1,1));

    ProjectionManager::setScissor(Vec2i::ZERO,size_i);
    ProjectionManager::setViewportProjection(Vec2i::ZERO,size_i);
}

void resize(int w, int h) {

    setupProjection(w,h);
    //ProjectionManager::updateView( Vec2i::ZERO, size_i );
//    ProjectionManager::setupPro jection( size_i, size_d );

    GuiManager::OnResize( ProjectionManager::getViewportObjSize() );

}

void MouseFunc(int button, int state, int x, int y) {

//    print("Mouse:",x,ProjectionManager::SCR_SIZE.y-y);
//
//    print("Local:",ProjectionManager::unProject(Vec2i(x,ProjectionManager::SCR_SIZE.y-y)));

    Vec2d local_mpos = ProjectionManager::unProjectMouse(Vec2i(x,y));

    GuiManager::OnMouseDown(button, state, local_mpos);

}