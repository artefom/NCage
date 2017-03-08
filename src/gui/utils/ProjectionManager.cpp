//
// Created by artef on 04.03.2017.
//

#include "ProjectionManager.h"

//
Vec2i ProjectionManager::SCR_SIZE{1, 1};
Vec2d ProjectionManager::OBJ_SCALE{1, 1};

void ProjectionManager::setScreenSize(Vec2i size) {
    SCR_SIZE = size;
}

void ProjectionManager::setScale(Vec2d scale) {
    OBJ_SCALE = scale;
}

void ProjectionManager::setViewportProjection(Vec2i offset, Vec2i size) {

    vp_offset = offset;
    vp_size = size;



    //vp_scale = scale;

    glMatrixMode(GL_PROJECTION);

    // Load Identity mateix (clear)
    glLoadIdentity();

    glViewport(offset.x, offset.y, size.x, size.y);

    // Orthographic projection width beautiful pixel match!
    // OBJ_SCALE is, in fact, pixel size.
    glOrtho(0.0, (size.x) * OBJ_SCALE.x, (size.y) * OBJ_SCALE.y, 0.0, -1.0, 1.0);

    // So, translate view in fraction of pixel size
    // 0.325 does well (not 0.25 because line rendering does not use quads as pixels,
    // but rhombus instead)
    glTranslated(OBJ_SCALE.x * 0.325, OBJ_SCALE.y * 0.325, 0);

    resetScissor();

    glMatrixMode(GL_MODELVIEW);

    // Update viewport coordinates (Cache)
    glGetIntegerv(GL_VIEWPORT, viewport.data());
    glGetDoublev(GL_PROJECTION_MATRIX, projection.data());

}

void ProjectionManager::resetScissor() {
    scissor_offset = Vec2d::ZERO;
    scissor_size = vp_size;
    glScissor(scissor_offset.x, scissor_offset.y, scissor_size.x, scissor_size.y);
}

void ProjectionManager::setScissor(Vec2i offset, Vec2i size) {

    scissor_offset = offset;
    scissor_size = size;

    //print("Setting scissor to",offset,size);

    glScissor(offset.x, offset.y + 1, size.x, size.y);

}

void ProjectionManager::setScissorClamped(Vec2i offset, Vec2i size) {

    const Vec2i &p1 = scissor_offset;
    Vec2i p2 = p1 + scissor_size;

    Vec2i new_p1 = mutils::max(p1, offset);// Vec2i::apply<mutils::max>(p1,offset);
    Vec2i new_p2 = mutils::min(p2, offset + size); //Vec2i::apply<mutils::min>(p2,offset+size);

    if (new_p2.x < new_p1.x)
        new_p2.x = new_p1.x;
    if (new_p2.y < new_p1.y) {
        new_p2.y = new_p1.y;
    }

    scissor_offset = new_p1;
    scissor_size = new_p2 - new_p1;

    //print("Setting scissor to",offset,size);

    glScissor(scissor_offset.x, scissor_offset.y + 1, scissor_size.x, scissor_size.y);

}

void ProjectionManager::pushScissor() {
    //print("Scissor pushed. current values:",scissor_offset,scissor_size);

    scissor_offset_stack.push(scissor_offset);
    scissor_size_stack.push(scissor_size);
}

void ProjectionManager::popScissor() {

    //print("Scissor poped, Setting scissor to",scissor_offset_stack.top(),scissor_size_stack.top());

    setScissor(scissor_offset_stack.top(), scissor_size_stack.top());
    scissor_offset_stack.pop();
    scissor_size_stack.pop();

}

void ProjectionManager::pushViewportProjection() {

    pushScissor();
    vp_offset_stack.push(vp_offset);
    vp_size_stack.push(vp_size);

}

void ProjectionManager::popViewportProjection() {

    setViewportProjection(vp_offset_stack.top(), vp_size_stack.top());
    popScissor();

    vp_offset_stack.pop();
    vp_size_stack.pop();
}

Vec2d ProjectionManager::project_d(Vec2d pos) {
    std::array<GLdouble, 16> modelview;
    std::array<GLdouble, 3> screen_coords;

    //glGetDoublev(GL_PROJECTION_MATRIX, projection.data());
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview.data());
    //glGetIntegerv(GL_VIEWPORT,viewport.data());

    gluProject(pos.x, pos.y, 0,
               modelview.data(), projection.data(), viewport.data(),
               screen_coords.data(), screen_coords.data() + 1, screen_coords.data() + 2);

    return Vec2d(screen_coords[0], screen_coords[1]);
}

Vec2d ProjectionManager::unProject(Vec2i pos) {
    //std::array<GLdouble, 16> projection;
    std::array<GLdouble, 16> modelview;
    //std::array<GLint   , 4>  viewport;
    std::array<GLdouble, 3> screen_coords;

    //glGetDoublev(GL_PROJECTION_MATRIX, projection.data());
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview.data());
    //glGetIntegerv(GL_VIEWPORT,viewport.data());

    gluUnProject(pos.x, pos.y, 0,
                 modelview.data(), projection.data(), viewport.data(),
                 screen_coords.data(), screen_coords.data() + 1, screen_coords.data() + 2);

    return Vec2d(screen_coords[0], screen_coords[1]);
}

Vec2d ProjectionManager::unProjectMouse(Vec2i pos) {
    pos.y = SCR_SIZE.y - pos.y - 1;
    pos.x += 1;
    return unProject(pos);
}

Vec2i ProjectionManager::vp_size;
Vec2i ProjectionManager::vp_offset;
//Vec2d ProjectionManager::vp_scale = Vec2i::ONE;

std::stack<Vec2i> ProjectionManager::vp_offset_stack;
std::stack<Vec2i> ProjectionManager::vp_size_stack;
//std::stack<Vec2d> ProjectionManager::vp_scale_stack;

std::array<GLdouble, 16> ProjectionManager::projection;
std::array<GLint, 4>  ProjectionManager::viewport;


Vec2i ProjectionManager::scissor_offset;
Vec2i ProjectionManager::scissor_size;

std::stack<Vec2i> ProjectionManager::scissor_offset_stack;
std::stack<Vec2i> ProjectionManager::scissor_size_stack;

//Vec2d ProjectionManager::LOC_SIZE{1,1};
