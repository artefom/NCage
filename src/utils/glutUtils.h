//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_GLUTUTILS_H
#define PLAYIN_GLUTUTILS_H

#include <string>
#include <ios>
#include <freeglut.h>

#include "Vec2d.h"

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


    Color(const char* str) {
        from_string(str);
    }

    Color(std::string str) {
        from_string( str.c_str() );
    }

private:

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

#endif //PLAYIN_GLUTUTILS_H
