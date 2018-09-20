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

#include <stdlib.h>
#include <GL/gl.h>
#include <iostream>


namespace LinearGL
{
    extern const double PI;


    template <size_t N>
    struct vec
    {
        static_assert(N == 2 || N == 3 || N == 4,
                      "Only vec's with N = 2,3,4 are supported");
    };


    template<>
    struct vec<2>
    {
        union
        {
            GLfloat coords[2];
            struct { GLfloat x, y; };
            struct { GLfloat u, v; };
        };

        GLfloat &operator[](const size_t i);
        const GLfloat &operator[](const size_t i) const;

        vec(void);
        vec(const GLfloat x, const GLfloat y);
    };

    typedef vec<2> vec2;


    template<>
    struct vec<3>
    {
        union
        {
            GLfloat coords[3];
            struct { GLfloat x, y, z; };
        };

        GLfloat &operator[](const size_t i);
        const GLfloat &operator[](const size_t i) const;

        vec(void);
        vec(const vec<2> &, const GLfloat z);
        vec(const GLfloat x, const GLfloat y, const GLfloat z);

        vec<2> xy(void);
    };

    typedef vec<3> vec3;


    template<>
    struct vec<4>
    {
        union
        {
            GLfloat coords[4];
            struct { GLfloat x, y, z, w; };
        };

        GLfloat &operator[](const size_t i);
        const GLfloat &operator[](const size_t i) const;

        vec(void);
        vec(const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);
        vec(const vec<3> &, const GLfloat w);

        vec<3> xyz(void);
    };

    typedef vec<4> vec4;


    template <size_t N>
    vec<N> &operator+=(vec<N> &v1, const vec<N> &v2);

    template <size_t N>
    vec<N> &operator-=(vec<N> &v1, const vec<N> &v2);

    template <size_t N>
    vec<N> operator+(const vec<N> &v1, const vec<N> &v2);

    template <size_t N>
    vec<N> operator-(const vec<N> &v1, const vec<N> &v2);

    template <size_t N>
    vec<N> operator-(const vec<N> &v);

    template <size_t N>
    vec<N> operator*(const vec<N> &v, const GLfloat scalar);

    template <size_t N>
    vec<N> operator*(const GLfloat scalar, const vec<N> &v);

    template <size_t N>
    vec<N> operator/(const vec<N> &v, const GLfloat scalar);

    template <size_t N>
    vec<N> &operator*=(vec<N> &v, const GLfloat scalar);

    template <size_t N>
    vec<N> &operator/=(vec<N> &v, const GLfloat scalar);

    template <size_t N>
    bool operator==(const vec<N> &v1, const vec<N> &v2);

    template <size_t N>
    bool operator!=(const vec<N> &v1, const vec<N> &v2);

    template <size_t N>
    std::ostream& operator<<(std::ostream& os, const vec<N> v);

    template <size_t N>
    vec<N> Unit(const vec<N> &v);

    template <size_t N>
    GLfloat Length(const vec<N> &v);

    template <size_t N>
    GLfloat Length2(const vec<N> &v);

    template <size_t N>
    GLfloat Dot(const vec<N> &v1, const vec<N> &v2);

    template <size_t N>
    GLfloat Angle(const vec<N> &v1, const vec<N> &v2);

    vec3 Cross(const vec3 &v1, const vec3 &v2);

    vec4 Cross(const vec4 &v1, const vec4 &v2);
}

#endif  // VEC_H
