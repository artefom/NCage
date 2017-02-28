//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_VEC2D_H
#define PLAYIN_VEC2D_H


struct Vec2d {
public:

    double x;
    double y;

    inline Vec2d() {
        x = 0;
        y = 0;
    }

    inline Vec2d(const Vec2d& ref){
        x = ref.x;
        y = ref.y;
    }

    inline Vec2d(Vec2d&& ref) {
        x = ref.x;
        y = ref.y;
    }

    inline Vec2d(double i_x, double i_y) {
        x = i_x;
        y = i_y;
    }

    inline Vec2d& operator*=(const Vec2d& rhs) { x *= rhs.x; y *= rhs.y; return *this; };
    inline Vec2d& operator*=(double rhs) {x *= rhs; y*=rhs; return *this;};

    inline Vec2d& operator/=(const Vec2d& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
    inline Vec2d& operator/=(double rhs) {x /= rhs; y/=rhs; return *this;};

    inline Vec2d& operator+=(const Vec2d& rhs) { x += rhs.x; y += rhs.y; return *this; };
    inline Vec2d& operator+=(const double& k) { x += k; y += k; return *this; };;

    inline Vec2d& operator-=(const Vec2d& rhs) { x -= rhs.x; y -= rhs.y; return *this; };
    inline Vec2d& operator-=(const double& k) { x -= k; y -= k; return *this; };

    // Copy assignment
    inline Vec2d& operator=(const Vec2d& other) {x = other.x; y = other.y; return *this; };

    //Move assignment
    Vec2d& operator=(Vec2d&& other) noexcept {
        x = other.x;
        y = other.y;
        return *this;
    }

    static const Vec2d ZERO;
    static const Vec2d ONE;

};

inline Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs) { return Vec2d(lhs.x+rhs.x,lhs.y+rhs.y); };
inline Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs) { return Vec2d(lhs.x-rhs.x,lhs.y-rhs.y); };

inline Vec2d operator+(const Vec2d& lhs, double rhs) { return Vec2d(lhs.x+rhs,lhs.y+rhs); }
inline Vec2d operator-(const Vec2d& lhs, double rhs) { return Vec2d(lhs.x-rhs,lhs.y-rhs); };

inline Vec2d operator*(const Vec2d& lhs, double rhs) { return Vec2d(lhs.x*rhs,lhs.y*rhs); };
inline Vec2d operator/(const Vec2d& lhs, double rhs) { return Vec2d(lhs.x/rhs,lhs.y/rhs); };

inline Vec2d operator*(const Vec2d& lhs, const Vec2d& rhs) { return Vec2d(lhs.x*rhs.x,lhs.y*rhs.y); };
inline Vec2d operator/(const Vec2d& lhs, const Vec2d& rhs) { return Vec2d(lhs.x/rhs.x,lhs.y/rhs.y); };

inline Vec2d operator-(const Vec2d& rhs) {return Vec2d(-rhs.x,-rhs.y);};


#endif //PLAYIN_VEC2D_H
