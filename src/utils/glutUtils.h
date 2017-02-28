//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_GLUTUTILS_H
#define PLAYIN_GLUTUTILS_H

#include <string>
#include <ios>
#include <freeglut.h>

#include "Vec2d.h"
#include "mathUtils.h"

class Color {

public:

    union {
        unsigned int code;
        struct {
            unsigned char b;
            unsigned char g;
            unsigned char r;
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

private:

    // Creates color from string
    inline void from_string(const char* str) {

        if (str == 0)
            return;

        if (str[0] == 0) return;

        if (str[0] == '0' and str[1] == 'x') {
            code = std::stoul(str, nullptr, 16);

            size_t str_length = strlen(str);
            if (str_length <= 8) {
                a = 255;
            }
        }


    }

};

inline void drawRect(Vec2d p1, Vec2d p2) {
    glBegin(GL_QUADS);
    glVertex2d(p1.x, p1.y);
    glVertex2d(p2.x, p1.y);
    glVertex2d(p2.x, p2.y);
    glVertex2d(p1.x, p2.y);
    glEnd();
}

inline void glColor(Color c) {
    glColor4ub(c.r,c.g,c.b,c.a);
}

inline void glTranslate(Vec2d vec) {
    glTranslated(vec.x,vec.y,0);
}

inline void drawHRect(Vec2d p1, Vec2d p2) {
    glBegin(GL_LINE_LOOP);
    glVertex2d(p1.x, p1.y);
    glVertex2d(p2.x, p1.y);
    glVertex2d(p2.x, p2.y);
    glVertex2d(p1.x, p2.y);
    glEnd();
}

#endif //PLAYIN_GLUTUTILS_H
