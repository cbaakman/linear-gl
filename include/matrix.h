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

#ifndef MATRIX_H
#define MATRIX_H

#include "vec.h"
#include "quat.h"
#include "plane.h"


/**
 * column-major: the first number is the column, second is row.
 */
template <size_t N>
struct matrix
{
    static_assert(N == 2 || N == 3 || N == 4,
                  "Only matrices with N = 2,3,4 are supported");

    GLfloat m[N][N];

    GLfloat *operator[] (const size_t column);
    const GLfloat *operator[] (const size_t column) const;
};

typedef matrix<4> matrix4;

template<size_t N>
bool operator==(const matrix<N> &, const matrix<N> &);

template<size_t N>
bool operator!=(const matrix<N> &, const matrix<N> &);

template<size_t N>
std::ostream &operator<<(std::ostream &, const matrix<N> &);

template <size_t N>
GLfloat Determinant(const matrix<N> &);

template <size_t N>
matrix<N> MatInverse(const matrix<N> &);

template <size_t N>
matrix<N> MatTranspose(const matrix<N> &);

matrix4 MatID(void);

matrix4 MatTranslate(const vec3 &);

matrix4 MatRotAxis(const vec3 &axis, float angle);  // radians

matrix4 MatQuat(const quaternion &q);  // also a rotation matrix

matrix4 MatScale(const GLfloat s);
matrix4 MatScale(const GLfloat sx, const GLfloat sy, const GLfloat sz);

matrix4 MatReflect(const plane3 &);

template <size_t N>
matrix<N> operator*(const matrix<N> &, const matrix<N> &);

template <size_t N>
matrix<N> operator*(const matrix<N> &, const GLfloat);

template <size_t N>
matrix<N> operator*(const GLfloat, const matrix<N> &);

template <size_t N>
matrix<N> operator/(const matrix<N> &, const GLfloat);

template <size_t N>
matrix<N> &operator*=(matrix<N> &, const GLfloat);

template <size_t N>
matrix<N> &operator/=(matrix<N> &, const GLfloat);

vec4 operator*(const matrix4 &, const vec4 &);

vec3 operator*(const matrix4 &, vec3 &);

GLfloat *operator&(matrix4 &);

const GLfloat *operator&(const matrix4 &);

#endif  // MATRIX_H
