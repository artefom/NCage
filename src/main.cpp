#define DEBUG

#include <iostream>
#include <freeglut.h>
#include <thread>

#include "utils/thread_factory.h"
#include "constants.h"

using namespace std;

class A {
    public:

    A() {
        cout << "A created!" << endl;
    }

    ~A() {
        cout << "A destroyed!" << endl;
    }

    void sayhello() {
        cout << "Hello, world!";
    }
};

int main(int argc, cstring argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Ass class destroyer");

    AsyncClassManager<A> AManager{};

    AManager.call( &A::sayhello );

    Sleep(100);
    cout << "Success!" << endl;

    return 0;
}