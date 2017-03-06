//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_MATHUTILS_H
#define PLAYIN_MATHUTILS_H

#include <cmath>
#include "Vec2d.h"

namespace mutils {
// Maps value from one range to another


    Vec2d map(Vec2d value, Vec2d from_min, Vec2d from_max, Vec2d to_min, Vec2d to_max);

    template<class FROM, class TO>
    inline TO map(FROM value, FROM from_min, FROM from_max, TO to_min, TO to_max) {
        return (TO)(value - from_min) / (TO)(from_max - from_min) * (to_max - to_min) + to_min;
    };

    template<class T1, class T2, class T3> inline T1 clamp(T1 value, T2 min, T3 max) {
        if (value > max) value = (T1)max;
        else if (value < min) value = (T1)min;
        return value;
    }

    template<class T>
    inline bool isnan_any(Vec2<T> vec) {
        return std::isnan(vec.x) || std::isnan(vec.y);
    }

    template<class T>
    inline bool isinf_any(Vec2<T> vec) {
        return std::isinf(vec.x) || std::isinf(vec.y);
    }

    template<class T>
    inline bool iszer_any(Vec2<T> vec) {
        return (vec.x == 0) || (vec.y == 0);
    }

    template<class T>
    inline bool isneg_any(Vec2<T> vec) {
        return (vec.x < 0) || (vec.y < 0);
    }

    template<class T>
    inline bool ispos_any(Vec2<T> vec) {
        return (vec.x > 0) || (vec.y > 0);
    }

    template<class T> Vec2<T> abs( Vec2<T> vec ) {
        return Vec2<T>(std::abs(vec.x),std::abs(vec.y));
    }

    template<class T> Vec2<T> round( Vec2<T> vec ) {
        return Vec2<T>(std::round(vec.x),std::round(vec.y));
    }

    template<class T> Vec2<T> floor( Vec2<T> vec ) {
        return Vec2<T>(std::round(vec.x),std::round(vec.y));
    }

    template<class T> Vec2<T> ceil( Vec2<T> vec ) {
        return Vec2<T>(std::round(vec.x),std::round(vec.y));
    }

    template<class T,T(F)(T)> Vec2<T> apply(Vec2<T> vec) {
        return Vec2<T>( F(vec.x),F(vec.y) );
    }

    template<class T,T(F)(T,T)> Vec2<T> apply(Vec2<T> vec1, Vec2<T> vec2) {
        return Vec2<T>( F(vec1.x,vec2.x),F(vec1.y,vec2.y) );
    }

    template<class T> T
    inline min (T v1, T v2) {
        return v1 > v2 ? v2 : v1;
    }

    template<class T> T
    inline max (T v1, T v2) {
        return v1 > v2 ? v1 : v2;
    }

}


#endif //PLAYIN_MATHUTILS_H
