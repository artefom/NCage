//
// Created by artef on 27.01.2017.
//

#include "Vec2d.h"

Vec2d operator+(const Vec2d &lhs, const Vec2d &rhs) {
    return Vec2d(lhs.x+rhs.x,lhs.y+rhs.y);
}

Vec2d operator-(const Vec2d &lhs, const Vec2d &rhs) {
    return Vec2d(lhs.x-rhs.x,lhs.y-rhs.y);
}

Vec2d::Vec2d(const Vec2d &ref) {
    x = ref.x;
    y = ref.y;
}

Vec2d::Vec2d(Vec2d &&ref) {
    x = ref.x;
    y = ref.y;
}

Vec2d::Vec2d(double i_x, double i_y) {
    x = i_x;
    y = i_y;
}

Vec2d &Vec2d::operator+=(const Vec2d &rhs) { x += rhs.x; y += rhs.y; return *this; }

Vec2d &Vec2d::operator+=(const double &k) { x += k; y += k; return *this; }

Vec2d &Vec2d::operator-=(const Vec2d &rhs) { x -= rhs.x; y -= rhs.y; return *this; }

Vec2d &Vec2d::operator-=(const double &k) { x -= k; y -= k; return *this; }

Vec2d &Vec2d::operator=(const Vec2d &other) {
    x = other.x;
    y = other.y;
    return *this;
}

const Vec2d Vec2d::ZERO{0,0};
const Vec2d Vec2d::ONE{1,1};
