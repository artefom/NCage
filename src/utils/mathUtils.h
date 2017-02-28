//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_MATHUTILS_H
#define PLAYIN_MATHUTILS_H

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

}


#endif //PLAYIN_MATHUTILS_H
