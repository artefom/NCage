//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_VEC2D_H
#define PLAYIN_VEC2D_H


template<class T>
struct Vec2 {
public:

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

template<class T>
inline Vec2<T> operator+(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x+rhs.x,lhs.y+rhs.y); };

template<class T>
inline Vec2<T> operator-(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x-rhs.x,lhs.y-rhs.y); };

template<class T>
inline Vec2<T> operator+(const Vec2<T>& lhs, double rhs) { return Vec2<T>(lhs.x+rhs,lhs.y+rhs); }

template<class T>
inline Vec2<T> operator-(const Vec2<T>& lhs, double rhs) { return Vec2<T>(lhs.x-rhs,lhs.y-rhs); };

template<class T>
inline Vec2<T> operator*(const Vec2<T>& lhs, double rhs) { return Vec2<T>(lhs.x*rhs,lhs.y*rhs); };

template<class T>
inline Vec2<T> operator/(const Vec2<T>& lhs, double rhs) { return Vec2<T>(lhs.x/rhs,lhs.y/rhs); };

template<class T>
inline Vec2<T> operator*(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x*rhs.x,lhs.y*rhs.y); };

template<class T>
inline Vec2<T> operator/(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs.x/rhs.x,lhs.y/rhs.y); };

template<class T>
inline Vec2<T> operator-(const Vec2<T>& rhs) {return Vec2<T>(-rhs.x,-rhs.y);};

typedef Vec2<double> Vec2d;
typedef Vec2<float> Vec2f;

typedef Vec2<int> Vec2i;


#endif //PLAYIN_VEC2D_H
