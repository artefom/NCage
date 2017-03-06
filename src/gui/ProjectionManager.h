//
// Created by artef on 04.03.2017.
//

#ifndef PLAYIN_PROJECTIONMANAGER_H
#define PLAYIN_PROJECTIONMANAGER_H

#include <Vec2d.h>
#include <array>
#include <stack>

#include "glutUtils.h"

class ProjectionManager {

private:

    // Cache viewport and projection matrices
    static std::array<GLdouble, 16> projection;
    static std::array<GLint   , 4>  viewport;

public:

    static Vec2i SCR_SIZE;
    static Vec2i VP_SIZE;
    static Vec2i VP_OFFSET;
    static Vec2d OBJ_SCALE;

    static Vec2i scissor_offset;
    static Vec2i scissor_size;

    static std::stack<Vec2i> vp_offset_stack;
    static std::stack<Vec2i> vp_size_stack;
    //static std::stack<Vec2d> vp_scale_stack;

    static std::stack<Vec2i> scissor_offset_stack;
    static std::stack<Vec2i> scissor_size_stack;

    // Sets screen size, so mouse coordinates can be converted nicely
    static void setScreenSize(Vec2i size) {
        SCR_SIZE = size;
    }

    static void setScale(Vec2d scale) {
        OBJ_SCALE = scale;
    }

    static Vec2i vp_size;
    static Vec2i vp_offset;

    //static Vec2d vp_scale;

    static void setViewportProjection(Vec2i offset, Vec2i size) {

        vp_offset = offset;
        vp_size = size;
        //vp_scale = scale;

        glMatrixMode(GL_PROJECTION);

        // Load Identity mateix (clear)
        glLoadIdentity();

        glViewport(offset.x, offset.y, size.x, size.y);

        // Orthographic prohection size fixed!
        glOrtho(0.0, (size.x)*OBJ_SCALE.x, (size.y)*OBJ_SCALE.y, 0.0, -1.0, 1.0);
        glTranslated(OBJ_SCALE.x*0.325,OBJ_SCALE.y*0.325,0);

        //glScissor(offset.x, offset.y, size.x, size.y);
        //glEnable(GL_SCISSOR_TEST);

        glMatrixMode(GL_MODELVIEW);

        // Update viewport coordinates (Cache)
        glGetIntegerv(GL_VIEWPORT,viewport.data());
        glGetDoublev(GL_PROJECTION_MATRIX, projection.data());

    };

    static void setScissor(Vec2i offset, Vec2i size) {

        scissor_offset = offset;
        scissor_size = size;

        glEnable(GL_SCISSOR_TEST);
        glScissor(offset.x,offset.y,size.x,size.y);

    }

    static void pushScissor() {
        scissor_offset_stack.push(scissor_offset);
        scissor_size_stack.push(scissor_size);
    }

    static void popScissor() {

        setScissor(scissor_offset_stack.top(), scissor_size_stack.top());
        scissor_offset_stack.pop();
        scissor_size_stack.pop();

    }

//    static void setViewportProjection(Vec2i offset, Vec2i size) {
//        setViewportProjection(offset,size,Vec2d(1,1));
//    };


    static void pushViewportProjection() {

        vp_offset_stack.push(vp_offset);
        vp_size_stack.push(vp_size);
        //vp_scale_stack.push(vp_scale);

//        glPushAttrib(GL_SCISSOR_BIT);
//        glPushAttrib(GL_PROJECTION_MATRIX);
        //Update cache
//        glGetIntegerv(GL_VIEWPORT,viewport.data());
//        glGetDoublev(GL_PROJECTION_MATRIX, projection.data());
    }

    static void popViewportProjection() {

        setViewportProjection( vp_offset_stack.top(),vp_size_stack.top() );

        vp_offset_stack.pop();
        vp_size_stack.pop();
        //vp_scale_stack.pop();

//        glPopAttrib();
//        glPopAttrib();
        //Update cache
//        glGetIntegerv(GL_VIEWPORT,viewport.data());
//        glGetDoublev(GL_PROJECTION_MATRIX, projection.data());
    }

    static Vec2i getViewportSize() {
        return Vec2i(viewport[2],viewport[3]);
    }

    static Vec2i getViewportPosition() {
        return Vec2i(viewport[0],viewport[1]);
    }

    // Get size of viewport in object coordinates
    static Vec2d getViewportObjSize() {
        return mutils::abs( unProject( getViewportPosition()+getViewportSize() )-getViewportObjPosition() );
    }

    // Get
    static Vec2d getViewportObjPosition() {
        return unProject( getViewportPosition() );
    }

    static Vec2d project_d(Vec2d pos) {
        std::array<GLdouble, 16> modelview;
        std::array<GLdouble, 3>  screen_coords;

        //glGetDoublev(GL_PROJECTION_MATRIX, projection.data());
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview.data());
        //glGetIntegerv(GL_VIEWPORT,viewport.data());

        gluProject(pos.x,pos.y,0,
                   modelview.data(),projection.data(),viewport.data(),
                   screen_coords.data(),screen_coords.data()+1,screen_coords.data()+2);

        return Vec2d(screen_coords[0],screen_coords[1]);
    }

    static Vec2i project_i(Vec2d pos) {
        return Vec2i(project_d(pos));
    }

    static Vec2d unProject(Vec2i pos) {
        //std::array<GLdouble, 16> projection;
        std::array<GLdouble, 16> modelview;
        //std::array<GLint   , 4>  viewport;
        std::array<GLdouble, 3>  screen_coords;

        //glGetDoublev(GL_PROJECTION_MATRIX, projection.data());
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview.data());
        //glGetIntegerv(GL_VIEWPORT,viewport.data());

        gluUnProject(pos.x,pos.y,0,
                   modelview.data(),projection.data(),viewport.data(),
                   screen_coords.data(),screen_coords.data()+1,screen_coords.data()+2);

        return Vec2d(screen_coords[0],screen_coords[1]);
    }

    static Vec2d unProjectMouse(Vec2i pos) {
        pos.y = SCR_SIZE.y - pos.y;
        return unProject(pos);
    }

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
