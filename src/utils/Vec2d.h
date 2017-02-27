//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_VEC2D_H
#define PLAYIN_VEC2D_H


struct Vec2d {
public:

    double x;
    double y;

    Vec2d(const Vec2d& ref);

    Vec2d(Vec2d&& ref);

    Vec2d(double i_x, double i_y);

    Vec2d& operator+=(const Vec2d& rhs);
    Vec2d& operator+=(const double& k);

    Vec2d& operator-=(const Vec2d& rhs);
    Vec2d& operator-=(const double& k);

    // Copy assignment
    Vec2d& operator=(const Vec2d& other);

    //Move assignment
    Vec2d& operator=(Vec2d&& other) noexcept {
        x = other.x;
        y = other.y;
        return *this;
    }

    static const Vec2d ZERO;
    static const Vec2d ONE;

};

Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs);
Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs);


#endif //PLAYIN_VEC2D_H
