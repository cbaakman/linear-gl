/* Copyright (C) 2018 Coos Baakman
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef VEC_H
#define VEC_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <GL/gl.h>
#include <iostream>

const double PI = acos(-1.0);


#define VEC_SUBSCRIPT  GLfloat &operator[](const uintmax_t i) { return v[i]; }
#define CONST_VEC_SUBSCRIPT  const GLfloat &operator[](const uintmax_t i) const { return v[i]; }
#define VEC_DEFAULT_CONSTRUCTOR vec(void) {}


template <size_t N>
struct vec
{
    GLfloat v[N];

    VEC_SUBSCRIPT
    CONST_VEC_SUBSCRIPT
    VEC_DEFAULT_CONSTRUCTOR
};


template<>
struct vec<2>
{
    union
    {
        GLfloat v[2];
        struct { GLfloat x, y; };
    };

    VEC_SUBSCRIPT
    CONST_VEC_SUBSCRIPT
    VEC_DEFAULT_CONSTRUCTOR

    vec(const GLfloat _x, const GLfloat _y): x(_x), y(_y) {}
};


template<>
struct vec<3>
{
    union
    {
        GLfloat v[3];
        struct { GLfloat x, y, z; };
    };

    VEC_SUBSCRIPT
    CONST_VEC_SUBSCRIPT
    VEC_DEFAULT_CONSTRUCTOR

    vec(const GLfloat _x, const GLfloat _y, const GLfloat _z): x(_x), y(_y), z(_z) {}
};


template<>
struct vec<4>
{
    union
    {
        GLfloat v[4];
        struct { GLfloat x, y, z, w; };
    };

    VEC_SUBSCRIPT
    CONST_VEC_SUBSCRIPT
    VEC_DEFAULT_CONSTRUCTOR

    vec(const GLfloat _x, const GLfloat _y, const GLfloat _z, const GLfloat _w): x(_x), y(_y), z(_z), w(_w) {}

    vec(const vec<3> &v, const GLfloat _w): x(v.x), y(v.y), z(v.z), w(_w) {}

    vec<3> xyz(void)
    {
        return {x, y, z};
    }
};

template <int N>
inline vec<N> &operator+=(vec<N> &v1, const vec<N> &v2)
{
    size_t i;
    for(i = 0; i < N; i++)
        v1[i] += v2[i];
    return v1;
}

template <int N>
inline vec<N> &operator-=(vec<N> &v1, const vec<N> &v2)
{
    size_t i;
    for(i = 0; i < N; i++)
        v1[i] -= v2[i];
    return v1;
}

template <size_t N>
inline const vec<N> operator+(const vec<N> &v1, const vec<N> &v2)
{
    vec<N> sum;
    size_t i = 0;
    for (i = 0; i < N; i++)
        sum[i] = v1[i] + v2[i];
    return sum;
}

template <size_t N>
inline const vec<N> operator-(const vec<N> &v1, const vec<N> &v2)
{
    vec<N> sub;
    size_t i = 0;
    for (i = 0; i < N; i++)
        sub[i] = v1[i] - v2[i];
    return sub;
}

template <size_t N>
inline const vec<N> operator-(const vec<N> &v)
{
    vec<N> neg;
    size_t i = 0;
    for (i = 0; i < N; i++)
        neg[i] = -v[i];
    return neg;
}

template <size_t N>
inline const vec<N> operator*(const vec<N> &v, const GLfloat scalar)
{
    vec<N> mul;
    size_t i = 0;
    for (i = 0; i < N; i++)
        mul[i] = v[i] * scalar;
    return mul;
}

template <size_t N>
inline const vec<N> operator*(const GLfloat scalar, const vec<N> &v)
{
    return v * scalar;
}

template <size_t N>
inline const vec<N> operator/(const vec<N> &v, const GLfloat scalar)
{
    vec<N> div;
    size_t i = 0;
    for (i = 0; i < N; i++)
        div[i] = v[i] / scalar;
    return div;
}

template <int N>
inline vec<N> &operator*=(vec<N> &v, const GLfloat scalar)
{
    size_t i;
    for(i = 0; i < N; i++)
        v[i] *= scalar;
    return v;
}

template <int N>
inline vec<N> &operator/=(vec<N> &v, const GLfloat scalar)
{
    size_t i;
    for(i = 0; i < N; i++)
        v[i] /= scalar;
    return v;
}

template <size_t N>
inline bool operator==(const vec<N> &v1, const vec<N> &v2)
{
    size_t i = 0;
    for (i = 0; i < N; i++)
        if (v1[i] != v2[i])
            return false;

    return true;
}
template <size_t N>
inline bool operator!=(const vec<N> &v1, const vec<N> &v2)
{
    size_t i = 0;
    for (i = 0; i < N; i++)
        if (v1[i] != v2[i])
            return true;

    return false;
}

template <size_t N>
inline std::ostream& operator<<(std::ostream& os, const vec<N> v)
{
    os << "{";
    size_t i = 0;
    for (i = 0; i < N; i++)
    {
        if (i > 0)
            os << ", ";
        os << v[i];
    }
    os << "}";
    return os;
}

template <size_t N>
inline vec<N> Unit(const vec<N> &v)
{
    return v / Length(v);
}

template <size_t N>
inline GLfloat Length(const vec<N> &v)
{
    return sqrt(Length2(v));
}

template <size_t N>
inline GLfloat Length2(const vec<N> &v)
{
    GLfloat l2 = 0.0f;
    size_t i;
    for (i = 0; i < N; i++)
        l2 += v[i] * v[i];
    return l2;
}

template <size_t N>
inline GLfloat Dot(const vec<N> &v1, const vec<N> &v2)
{
    GLfloat r = 0.0f;
    size_t i;
    for (i = 0; i < N; i++)
        r += v1[i] * v2[i];
    return r;
}

template <size_t N>
inline GLfloat Angle(const vec<N> &v1, const vec<N> &v2)
{
    GLfloat dot = Dot(v1.Unit(), v2.Unit());

    if (dot > 0.99999999)
        return 0.0f;
    else if (dot < -0.99999999)
        return PI;

    return acos(dot);
}

typedef vec<3> vec3;

inline vec3 Cross(const vec3 &v1, const vec3 &v2)
{
    return {v1.y * v2.z - v2.y * v1.z,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x};
}

typedef vec<4> vec4;

inline vec4 Cross(const vec4 &v1, const vec4 &v2)
{
    return {v1.y * v2.z - v1.z * v2.y + v1.x * v2.w + v1.w * v2.x,
            v1.z * v2.x - v1.x * v2.z + v1.y * v2.w + v1.w * v2.y,
            v1.x * v2.y - v1.y * v2.x + v1.z * v2.w + v1.w * v2.z,
            v1.w * v2.w - v1.x * v2.x - v1.y * v2.y - v1.z * v2.z};
}

#endif  // VEC_H
