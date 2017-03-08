//
// Created by artef on 04.03.2017.
//

#ifndef PLAYIN_PROJECTIONMANAGER_H
#define PLAYIN_PROJECTIONMANAGER_H

#include <Vec2d.h>
#include <array>
#include <stack>
#include <cassert>

#include "glutUtils.h"

class ProjectionManager {

private:

    // Cache viewport and projection matrices
    static std::array<GLdouble, 16> projection;
    static std::array<GLint, 4> viewport;

public:

    static Vec2i SCR_SIZE;
    static Vec2d OBJ_SCALE;

    static Vec2i scissor_offset;
    static Vec2i scissor_size;

    static std::stack<Vec2i> vp_offset_stack;
    static std::stack<Vec2i> vp_size_stack;
    //static std::stack<Vec2d> vp_scale_stack;

    static std::stack<Vec2i> scissor_offset_stack;
    static std::stack<Vec2i> scissor_size_stack;

    // Sets screen size, so mouse coordinates can be converted nicely
    static void setScreenSize(Vec2i size);

    static void setScale(Vec2d scale);

    static Vec2i vp_size;
    static Vec2i vp_offset;

    //static Vec2d vp_scale;

    static void setViewportProjection(Vec2i offset, Vec2i size);;

    static void resetScissor();

    static void setScissor(Vec2i offset, Vec2i size);

    // Set scissor in respect with previously set scissors
    // Newly formed scissor will not intersect with area, cutted of by
    // current scissor.
    static void setScissorClamped(Vec2i offset, Vec2i size);

    static void pushScissor();

    static void popScissor();

//    static void setViewportProjection(Vec2i offset, Vec2i size) {
//        setViewportProjection(offset,size,Vec2d(1,1));
//    };


    static void pushViewportProjection();

    static void popViewportProjection();

    static inline Vec2i getViewportSize() {
        return Vec2i(viewport[2], viewport[3]);
    }

    static inline Vec2i getViewportPosition() {
        return Vec2i(viewport[0], viewport[1]);
    }

    // Get size of viewport in object coordinates
    static inline Vec2d getViewportObjSize() {
        return Vec2d::apply<std::abs>(unProject(getViewportPosition() + getViewportSize()) - getViewportObjPosition());
    }

    // Get
    static inline Vec2d getViewportObjPosition() {
        return unProject(getViewportPosition());
    }

    static Vec2d project_d(Vec2d pos);

    static inline Vec2i project_i(Vec2d pos) {
        return Vec2i(project_d(pos));
    }

    static Vec2d unProject(Vec2i pos);

    static Vec2d unProjectMouse(Vec2i pos);

    static inline Vec2d getPixelSize() {
        return OBJ_SCALE;
    }

};

class safePushMatrix {
public:
    safePushMatrix() {
        glPushMatrix();
    }

    ~safePushMatrix() {
        glPopMatrix();
    }
};


#endif //PLAYIN_PROJECTIONMANAGER_H
