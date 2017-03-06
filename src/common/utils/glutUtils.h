//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_GLUTUTILS_H
#define PLAYIN_GLUTUTILS_H

#include <string>
#include <ios>
#include <glew.h>
#include <freeglut.h>
#include <iostream>

#include "Vec2d.h"
#include "mathUtils.h"

class Color {

public:

    union {
        unsigned int code;
        struct {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
    };


    Color();

    Color(unsigned char i_r, unsigned char i_g, unsigned char i_b, unsigned char i_a = 255);

    // Initialization of color by hex number in c_string
    Color(const char* str);

    // Initialization of color by hex number
    Color(std::string str);

    static Color mix(Color c1, Color c2, double alpha) {
        unsigned char r = (unsigned char)mutils::clamp( c1.r*(1-alpha)+c2.r*alpha, 0, 255);
        unsigned char g = (unsigned char)mutils::clamp( c1.g*(1-alpha)+c2.g*alpha, 0, 255);
        unsigned char b = (unsigned char)mutils::clamp( c1.b*(1-alpha)+c2.b*alpha, 0, 255);
        return Color(r,g,b);
    }

    inline static Color gray(unsigned char intensity) {
        return Color(intensity,intensity,intensity);
    }

private:

    // Creates color from string
    inline void from_string(const char* str) {

        if (str == 0)
            return;

        if (str[0] == 0) return;

        if (str[0] == '0' and str[1] == 'x') {

            unsigned long bgra =std::stoul(str, nullptr, 16);
            unsigned char* colors = reinterpret_cast<unsigned char*>(&bgra);

            size_t str_length = strlen(str);
            if (str_length <= 8) {
                r = colors[2];
                g = colors[1];
                b = colors[0];
                a = 255;
            } else {
                r = colors[3];
                g = colors[2];
                b = colors[1];
                a = colors[0];
            }

        }


    }

};

inline void glVertex(Vec2<double> v) {
    glVertex2d(v.x,v.y);
}

inline void glVertex(Vec2<float> v) {
    glVertex2f(v.x,v.y);
}

inline void drawRect(Vec2<double> p1, Vec2<double> p2) {
    glBegin(GL_QUADS);
    glVertex2d(p1.x, p1.y);
    glVertex2d(p2.x, p1.y);
    glVertex2d(p2.x, p2.y);
    glVertex2d(p1.x, p2.y);
    glEnd();
}

inline void drawRect(Vec2<float> p1, Vec2<float> p2) {
    glBegin(GL_QUADS);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p1.x, p2.y);
    glEnd();
}

inline void glColor(Color c) {
    glColor4ub(c.r,c.g,c.b,c.a);
}

inline void glTranslate(Vec2<double> vec) {
    glTranslated(vec.x,vec.y,0);
}

inline void glTranslate(Vec2<float> vec) {
    glTranslatef(vec.x,vec.y,0);
}

inline void glScale(Vec2<double> vec) {
    glScaled(vec.x,vec.y,0);
}

inline void glScale(Vec2<float> vec) {
    glScalef(vec.x,vec.y,0);
}

inline void drawHRect(Vec2d p1, Vec2d p2) {
    glBegin(GL_LINE_LOOP);
    glVertex2d(p1.x, p1.y);
    glVertex2d(p2.x, p1.y);
    glVertex2d(p2.x, p2.y);
    glVertex2d(p1.x, p2.y);
    glEnd();
}

void print();

template<typename T, typename ...TAIL>
void print(const T &t, TAIL... tail)
{
    std::cout<<t<<' ';
    print(tail...);
}

template<GLenum T>
class pixelSize;

#define PXSIZE(e,x) template<> class pixelSize<e> { public: static const int size = x;};

PXSIZE(GL_RGBA,4)

#undef PXSIZE

#endif //PLAYIN_GLUTUTILS_H
