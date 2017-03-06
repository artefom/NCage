//
// Created by artef on 04.03.2017.
//

#include "ProjectionManager.h"
//
Vec2i ProjectionManager::SCR_SIZE{1,1};
Vec2i ProjectionManager::VP_SIZE{1,1};
Vec2i ProjectionManager::VP_OFFSET{1,1};
Vec2d ProjectionManager::OBJ_SCALE{1,1};

Vec2i ProjectionManager::vp_size;
Vec2i ProjectionManager::vp_offset;
//Vec2d ProjectionManager::vp_scale = Vec2i::ONE;

std::stack<Vec2i> ProjectionManager::vp_offset_stack;
std::stack<Vec2i> ProjectionManager::vp_size_stack;
//std::stack<Vec2d> ProjectionManager::vp_scale_stack;

std::array<GLdouble, 16> ProjectionManager::projection;
std::array<GLint   , 4>  ProjectionManager::viewport;


Vec2i ProjectionManager::scissor_offset;
Vec2i ProjectionManager::scissor_size;

std::stack<Vec2i> ProjectionManager::scissor_offset_stack;
std::stack<Vec2i> ProjectionManager::scissor_size_stack;

//Vec2d ProjectionManager::LOC_SIZE{1,1};
