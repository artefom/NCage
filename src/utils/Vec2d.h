//
// Created by artef on 27.01.2017.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
#ifndef PLAYIN_VEC2D_H
#define PLAYIN_VEC2D_H

#include <type_traits>


template<class T>
struct Vec2 {
public:

    typedef T ctype;

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

    static const Vec2 ONE;
    static const Vec2 ZERO;

};

template <class T>
const Vec2<T> Vec2<T>::ONE{1,1};
template <class T>
const Vec2<T> Vec2<T>::ZERO{0,0};


// OPERATIONS WITH VECTORS
template<class T>
inline Vec2<T> operator+(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x+rhs.x,lhs.y+rhs.y); };

template<class T>
inline Vec2<T> operator-(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x-rhs.x,lhs.y-rhs.y); };

template<class T>
inline Vec2<T> operator*(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x*rhs.x,lhs.y*rhs.y); };

template<class T>
inline Vec2<T> operator/(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x/rhs.x,lhs.y/rhs.y); };

// OPERATIONS WITH SCALARS
template<class T, class T2, typename = typename std::enable_if<std::is_arithmetic<T>::value, T2>::type >
inline Vec2<T> operator+(const Vec2<T>& lhs, T2 rhs) { return Vec2<T>(lhs.x+rhs,lhs.y+rhs); }

template<class T, class T2, typename = typename std::enable_if<std::is_arithmetic<T>::value, T2>::type >
inline Vec2<T> operator-(const Vec2<T>& lhs, T2 rhs) { return Vec2<T>(lhs.x-rhs,lhs.y-rhs); };

template<class T, class T2, typename = typename std::enable_if<std::is_arithmetic<T>::value, T2>::type >
inline Vec2<T> operator*(const Vec2<T>& lhs, T2 rhs) { return Vec2<T>(lhs.x*rhs,lhs.y*rhs); };

template<class T, class T2, typename = typename std::enable_if<std::is_arithmetic<T>::value, T2>::type >
inline Vec2<T> operator/(const Vec2<T>& lhs, T2 rhs) { return Vec2<T>(lhs.x/rhs,lhs.y/rhs); };

// OPERATIONS WITH SCALARS REVERSED

template<class T2, class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T2>::type >
inline Vec2<T> operator+(T2 lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs+rhs.x,lhs+rhs.y); }

template<class T2, class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T2>::type >
inline Vec2<T> operator-(T2 lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs-rhs.x,lhs-rhs.y); };

template<class T2, class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T2>::type >
inline Vec2<T> operator*(T2 lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs*rhs.x,lhs*rhs.y); };

template<class T2, class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T2>::type >
inline Vec2<T> operator/(T2 lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs/rhs.x,lhs/rhs.y); };


// UNARY MINUS
template<class T>
inline Vec2<T> operator-(const Vec2<T>& rhs) {return Vec2<T>(-rhs.x,-rhs.y);};

// TYPEDEFS
typedef Vec2<double> Vec2d;
typedef Vec2<float> Vec2f;

typedef Vec2<int> Vec2i;


#endif //PLAYIN_VEC2D_H

#pragma clang diagnostic pop