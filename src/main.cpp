#define DEBUG

#include <iostream>
#include <thread>
#include <queue>
#include <glutUtils.h>
#include <mathUtils.h>

#define bg(x) cout << string("BG: ")+string(x)+string("\n");
#define gui(x) cout << string("GUI: ")+string(x)+string("\n");


#include "constants.h"
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

bool shouldExit = false;

thread bg_thread;

int main(int argc, cstring argv[]) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);

    glShadeModel(GL_FLAT);                      // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    glEnable(GL_TEXTURE_2D);
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

    Vec2d local_mpos = ProjectionManager::screenToLocal( Vec2i(x,y) );

    GuiManager::OnMouseMove(local_mpos);

}

void renderScene(void) {

    // Clear all

    glClear(GL_COLOR_BUFFER_BIT);

    GuiManager::draw();

    glutPostRedisplay();
    glFlush();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void resize(int w, int h) {

    if (h == 0)
        h = 1;

    Vec2i size_i{w,h};
    Vec2d size_d{(double)w,(double)h};

    ProjectionManager::setupProjection( size_i, size_d );

    GuiManager::OnResize( size_d );

}

void MouseFunc(int button, int state, int x, int y) {
//
//    double new_x = mutils::map(x, 0, SCR_W, 0.0, Local_W);
//    double new_y = mutils::map(y, 0, SCR_H, 0.0, Local_H);
//
    Vec2d local_mpos = ProjectionManager::screenToLocal(Vec2i(x,y));
    GuiManager::OnMouseDown(button, state, local_mpos);

}