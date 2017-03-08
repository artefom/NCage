//
// Created by artef on 27.01.2017.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
#ifndef PLAYIN_VEC2D_H
#define PLAYIN_VEC2D_H

#include <type_traits>
#include <iostream>
#include <cstdint>


template<class T>
struct Vec2 {
public:

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
    typedef T ctype;
#pragma clang diagnostic pop

    T x;
    T y;

    inline Vec2() {
        x = 0;
        y = 0;
    }

    inline Vec2(const Vec2& ref){
        x = ref.x;
        y = ref.y;
    }

    inline Vec2(Vec2&& ref) {
        x = ref.x;
        y = ref.y;
    }

    inline Vec2(T i_x, T i_y) {
        x = i_x;
        y = i_y;
    }

    inline Vec2& operator*=(const Vec2& rhs) { x *= rhs.x; y *= rhs.y; return *this; };
    inline Vec2& operator*=(double rhs) {x *= rhs; y*=rhs; return *this;};

    inline Vec2& operator/=(const Vec2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
    inline Vec2& operator/=(double rhs) {x /= rhs; y/=rhs; return *this;};

    inline Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; };
    inline Vec2& operator+=(const T& k) { x += k; y += k; return *this; };;

    inline Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; };
    inline Vec2& operator-=(const T& k) { x -= k; y -= k; return *this; };

    // Copy assignment
    inline Vec2& operator=(const Vec2& other) {x = other.x; y = other.y; return *this; };

    //Move assignment
    Vec2& operator=(Vec2&& other) noexcept {
        x = other.x;
        y = other.y;
        return *this;
    }

    // Type casting overload

    template<class C > operator Vec2<C>() const {
        return Vec2<C>((C)x,(C)y);
    }

    // static math operations

    template<T(F)(T)>
    static Vec2<T> apply(Vec2<T> vec) {
        return Vec2<T>( F(vec.x),F(vec.y) );
    }

    template<T(F)(T,T)>
    static Vec2<T> apply(Vec2<T> vec1, Vec2<T> vec2) {
        return Vec2<T>( F(vec1.x,vec2.x),F(vec1.y,vec2.y) );
    }

    inline bool all() {
        return x && y;
    }

    inline bool any() {
        return x || y;
    }


    static const Vec2 ONE;
    static const Vec2 ZERO;

};

template <class T>
const Vec2<T> Vec2<T>::ONE{1,1};
template <class T>
const Vec2<T> Vec2<T>::ZERO{0,0};


// Cout operations

template<class T>
std::ostream& operator<< (std::ostream& os, const Vec2<T>& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}


// OPERATIONS WITH VECTORS
template<class T>
inline Vec2<T> operator+(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x+rhs.x,lhs.y+rhs.y); };

template<class T>
inline Vec2<T> operator-(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x-rhs.x,lhs.y-rhs.y); };

template<class T>
inline Vec2<T> operator*(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x*rhs.x,lhs.y*rhs.y); };

template<class T>
inline Vec2<T> operator/(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x/rhs.x,lhs.y/rhs.y); };

//#define define_ops_for(t)\
//template<class T>\
//inline Vec2<T> operator+(const Vec2<T>& lhs, t rhs) { return Vec2<T>(lhs.x+rhs,lhs.y+rhs); }\
//template<class T>\
//inline Vec2<T> operator-(const Vec2<T>& lhs, t rhs) { return Vec2<T>(lhs.x-rhs,lhs.y-rhs); };\
//template<class T>\
//inline Vec2<T> operator*(const Vec2<T>& lhs, t rhs) { return Vec2<T>(lhs.x*rhs,lhs.y*rhs); };\
//template<class T>\
//inline Vec2<T> operator/(const Vec2<T>& lhs, t rhs) { return Vec2<T>(lhs.x/rhs,lhs.y/rhs); };\
//template<class T>\
//inline Vec2<T> operator+(t lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs+rhs.x,lhs+rhs.y); }\
//template<class T>\
//inline Vec2<T> operator-(t lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs-rhs.x,lhs-rhs.y); };\
//template<class T>\
//inline Vec2<T> operator*(t lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs*rhs.x,lhs*rhs.y); };\
//template<class T>\
//inline Vec2<T> operator/(t lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs/rhs.x,lhs/rhs.y); };
//
//define_ops_for(char)
//define_ops_for(unsigned char)
//define_ops_for(short int)
//define_ops_for(unsigned short int)
//define_ops_for(int)
//define_ops_for(unsigned int)
//define_ops_for(long int)
//define_ops_for(unsigned long int)
//define_ops_for(long long int)
//define_ops_for(unsigned long long int)
//define_ops_for(float)
//define_ops_for(double)
//define_ops_for(long double)
//
//#undef define_ops_for


//// OPERATIONS WITH SCALARS

template<class T, class T2>
inline Vec2<T> operator+(const Vec2<T>& lhs, T2 rhs) { return Vec2<T>(lhs.x+rhs,lhs.y+rhs); }

template<class T, class T2>
inline Vec2<T> operator-(const Vec2<T>& lhs, T2 rhs) { return Vec2<T>(lhs.x-rhs,lhs.y-rhs); };

template<class T, class T2>
inline Vec2<T> operator*(const Vec2<T>& lhs, T2 rhs) { return Vec2<T>(lhs.x*rhs,lhs.y*rhs); };

template<class T, class T2>
inline Vec2<T> operator/(const Vec2<T>& lhs, T2 rhs) { return Vec2<T>(lhs.x/rhs,lhs.y/rhs); };

////// OPERATIONS WITH SCALARS REVERSED
//
//template<class T2, class T>
//inline Vec2<T> operator+(T2 lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs+rhs.x,lhs+rhs.y); }
//
//template<class T2, class T>
//inline Vec2<T> operator-(T2 lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs-rhs.x,lhs-rhs.y); };
//
//template<class T2, class T>
//inline Vec2<T> operator*(T2 lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs*rhs.x,lhs*rhs.y); };
//
//template<class T2, class T>
//inline Vec2<T> operator/(T2 lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs/rhs.x,lhs/rhs.y); };

// UNARY MINUS
template<class T>
inline Vec2<T> operator-(const Vec2<T>& rhs) {return Vec2<T>(-rhs.x,-rhs.y);};

// COMPARISON OPERATORS

template<class T>
inline Vec2<bool> operator>(const Vec2<T> &lhs, const Vec2<T> &rhs) {
    return Vec2<bool>(lhs.x > rhs.x, lhs.y > rhs.y);
};

template<class T>
inline Vec2<bool> operator<(const Vec2<T> &lhs, const Vec2<T> &rhs) {
    return Vec2<bool>(lhs.x > rhs.x, lhs.y > rhs.y);
};

template<class T>
inline Vec2<bool> operator>=(const Vec2<T> &lhs, const Vec2<T> &rhs) {
    return Vec2<bool>(lhs.x >= rhs.x, lhs.y >= rhs.y);
};

template<class T>
inline Vec2<bool> operator<=(const Vec2<T> &lhs, const Vec2<T> &rhs) {
    return Vec2<bool>(lhs.x <= rhs.x, lhs.y <= rhs.y);
};

template<class T>
inline Vec2<bool> operator==(const Vec2<T> &lhs, const Vec2<T> &rhs) {
    return Vec2<bool>(lhs.x == rhs.x, lhs.y == rhs.y);
};

template<class T>
inline Vec2<bool> operator!=(const Vec2<T> &lhs, const Vec2<T> &rhs) {
    return Vec2<bool>(lhs.x != rhs.x, lhs.y != rhs.y);
};

// TYPEDEFS

typedef Vec2<double> Vec2d;

typedef Vec2<int_fast32_t> Vec2i;

//Math functions

#endif //PLAYIN_VEC2D_H

#pragma clang diagnostic pop