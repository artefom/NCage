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

int SCR_W = 1;
int SCR_H = 1;
double Local_W = 1;
double Local_H = 1;

void PassiveMouseMove(int x, int y) {

    double lx = mutils::map(x, 0, SCR_W, 0.0, Local_W);
    double ly = mutils::map(y, 0, SCR_H, 0.0, Local_H);

    GuiManager::OnMouseMove(lx, ly);

}


void setupProjection(int screen_width, int screen_height, double width, double height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    SCR_W = screen_width;
    SCR_H = screen_height;
    Local_W = width;
    Local_H = height;

    glViewport(0, 0, screen_width, screen_height);
    glOrtho(0.0, width, height, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glDisable(GL_CULL_FACE);
    glMatrixMode(GL_MODELVIEW);
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

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    //float ratio =  w * 1.0 / h;

    setupProjection(w, h, w, h);
    GuiManager::OnResize(w, h);

}

void MouseFunc(int button, int state, int x, int y) {

    double new_x = mutils::map(x, 0, SCR_W, 0.0, Local_W);
    double new_y = mutils::map(y, 0, SCR_H, 0.0, Local_H);
    GuiManager::OnMouseDown(button, state, new_x, new_y);

}