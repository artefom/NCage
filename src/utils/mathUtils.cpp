//
// Created by artef on 27.02.2017.
//

#include "mathUtils.h"

Vec2d mutils::map(Vec2d value, Vec2d from_min, Vec2d from_max, Vec2d to_min, Vec2d to_max) {
    return Vec2d( mutils::map(value.x,from_min.x,from_max.x,to_min.x,to_max.x),
                  mutils::map(value.y,from_min.y,from_max.y,to_min.y,to_max.y));
};