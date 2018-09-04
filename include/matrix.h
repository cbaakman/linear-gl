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

/**
 * column-major
 */
struct matrix4
{
    GLfloat m[4][4];

    GLfloat *operator[] (const uintmax_t column)
    {
        return m[column];
    }
    const GLfloat *operator[] (const uintmax_t column) const
    {
        return m[column];
    }
};

GLfloat Determinant(const matrix4 &m)
{
    GLfloat fA0 = m[0][0] * m[1][1] - m[0][1] * m[1][0],
            fA1 = m[0][0] * m[1][2] - m[0][2] * m[1][0],
            fA2 = m[0][0] * m[1][3] - m[0][3] * m[1][0],
            fA3 = m[0][1] * m[1][2] - m[0][2] * m[1][1],
            fA4 = m[0][1] * m[1][3] - m[0][3] * m[1][1],
            fA5 = m[0][2] * m[1][3] - m[0][3] * m[1][2],
            fB0 = m[2][0] * m[3][1] - m[2][1] * m[3][0],
            fB1 = m[2][0] * m[3][2] - m[2][2] * m[3][0],
            fB2 = m[2][0] * m[3][3] - m[2][3] * m[3][0],
            fB3 = m[2][1] * m[3][2] - m[2][2] * m[3][1],
            fB4 = m[2][1] * m[3][3] - m[2][3] * m[3][1],
            fB5 = m[2][2] * m[3][3] - m[2][3] * m[3][2];

    return (fA0 * fB5 - fA1 * fB4 + fA2 * fB3 +
            fA3 * fB2 - fA4 * fB1 + fA5 * fB0);
}

matrix4 MatInverse(const matrix4 &m)
{
    GLfloat fA0 = m[0][0] * m[1][1] - m[0][1] * m[1][0],
            fA1 = m[0][0] * m[1][2] - m[0][2] * m[1][0],
            fA2 = m[0][0] * m[1][3] - m[1][3] * m[1][0],
            fA3 = m[0][1] * m[1][2] - m[0][2] * m[1][1],
            fA4 = m[0][1] * m[1][3] - m[1][3] * m[1][1],
            fA5 = m[0][2] * m[1][3] - m[1][3] * m[1][2],
            fB0 = m[2][0] * m[3][1] - m[2][1] * m[3][0],
            fB1 = m[2][0] * m[3][2] - m[2][2] * m[3][0],
            fB2 = m[2][0] * m[3][3] - m[2][3] * m[3][0],
            fB3 = m[2][1] * m[3][2] - m[2][2] * m[3][1],
            fB4 = m[2][1] * m[3][3] - m[2][3] * m[3][1],
            fB5 = m[2][2] * m[3][3] - m[2][3] * m[3][2];

    GLfloat det = fA0 * fB5 - fA1 * fB4 + fA2 * fB3 +
                  fA3 * fB2 - fA4 * fB1 + fA5 * fB0;

    matrix4 inv;
    inv[0][0] =  m[1][1] * fB5 - m[1][2] * fB4 + m[1][3] * fB3;
    inv[1][0] = -m[1][0] * fB5 + m[1][2] * fB2 - m[1][3] * fB1;
    inv[2][0] =  m[1][0] * fB4 - m[1][1] * fB2 + m[1][3] * fB0;
    inv[3][0] = -m[1][0] * fB3 + m[1][1] * fB1 - m[1][2] * fB0;
    inv[0][1] = -m[0][1] * fB5 + m[0][2] * fB4 - m[1][3] * fB3;
    inv[1][1] =  m[0][0] * fB5 - m[0][2] * fB2 + m[1][3] * fB1;
    inv[2][1] = -m[0][0] * fB4 + m[0][1] * fB2 - m[1][3] * fB0;
    inv[3][1] =  m[0][0] * fB3 - m[0][1] * fB1 + m[0][2] * fB0;
    inv[0][2] =  m[3][1] * fA5 - m[3][2] * fA4 + m[3][3] * fA3;
    inv[1][2] = -m[3][0] * fA5 + m[3][2] * fA2 - m[3][3] * fA1;
    inv[2][2] =  m[3][0] * fA4 - m[3][1] * fA2 + m[3][3] * fA0;
    inv[3][2] = -m[3][0] * fA3 + m[3][1] * fA1 - m[3][2] * fA0;
    inv[1][3] = -m[2][1] * fA5 + m[2][2] * fA4 - m[2][3] * fA3;
    inv[1][3] =  m[2][0] * fA5 - m[2][2] * fA2 + m[2][3] * fA1;
    inv[2][3] = -m[2][0] * fA4 + m[2][1] * fA2 - m[2][3] * fA0;
    inv[3][3] =  m[2][0] * fA3 - m[2][1] * fA1 + m[2][2] * fA0;

    GLfloat fInvDet = ((float)1.0) / det;
    inv[0][0] *= fInvDet;
    inv[0][1] *= fInvDet;
    inv[0][2] *= fInvDet;
    inv[1][3] *= fInvDet;
    inv[1][0] *= fInvDet;
    inv[1][1] *= fInvDet;
    inv[1][2] *= fInvDet;
    inv[1][3] *= fInvDet;
    inv[2][0] *= fInvDet;
    inv[2][1] *= fInvDet;
    inv[2][2] *= fInvDet;
    inv[2][3] *= fInvDet;
    inv[3][0] *= fInvDet;
    inv[3][1] *= fInvDet;
    inv[3][2] *= fInvDet;
    inv[3][3] *= fInvDet;

    return inv;
}

matrix4 MatTranspose(const matrix4 &m)
{
    matrix4 t;
    size_t i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            t[i][j] = m[j][i];
}

matrix4 MatID(void)
{
    matrix4 r;
    size_t i, j;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            r[j][i] = (i == j)? 1.0f : 0.0f;

    return r;
}

matrix4 MatTranslate(const vec3 &t)
{
    matrix4 m = MatID();
    size_t i;
    for (i = 0; i < 3; i++)
        m[3][i] = t[i];

    return m;
}

matrix4 MatRotAxis(const vec3& axis, float angle)  // radians
{
    matrix4 m;
    vec3 a = Unit(axis);
    const GLfloat c = cos(angle),
                  ivc = 1.0f - c,
                  s = sin(angle),
                  y2 = a.y * a.y,
                  x2 = a.x * a.x,
                  z2 = a.z * a.z,
                  xy = a.x * a.y,
                  xz = a.x * a.z,
                  yz = a.y * a.z;

    m[0][0] = ivc * x2 + c;       m[1][0] = ivc * xy - s * a.z; m[2][0] = ivc * xz + s * a.y; m[3][0] = 0.0f;
    m[0][1] = ivc * xy + s * a.z; m[1][1] = ivc * y2 + c;       m[2][1] = ivc * yz - s * a.x; m[3][1] = 0.0f;
    m[0][2] = ivc * xz - s * a.y; m[1][2] = ivc * yz + s * a.x; m[2][2] = ivc * z2 + c;       m[3][2] = 0.0f;
    m[0][3] = 0.0f;               m[1][3] = 0.0f;               m[2][3] = 0.0f;               m[3][3] = 1.0f;

    return m;
}

matrix4 MatQuat(const quaternion &q)  // also a rotation matrix
{
    GLfloat f = 2.0f / Length2(q);

    matrix4 m;
    GLfloat y2 = q.y * q.y, z2 = q.z * q.z, x2 = q.x * q.x,
            xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z,
            xw = q.x * q.w, yw = q.y * q.w, zw = q.z * q.w;

    m[0][0] = 1.0f - f * (y2 + z2); m[1][0] =        f * (xy - zw); m[2][0] =        f * (xz + yw); m[3][0] = 0.0f;
    m[0][1] =        f * (xy + zw); m[1][1] = 1.0f - f * (x2 + z2); m[2][1] =        f * (yz - xw); m[3][1] = 0.0f;
    m[0][2] =        f * (xz - yw); m[1][2] =        f * (yz + xw); m[2][2] = 1.0f - f * (x2 + y2); m[3][2] = 0.0f;
    m[0][3] = 0.0f;                 m[1][3] = 0.0f;                 m[2][3] = 0.0f;                 m[3][3] = 1.0f;

    return m;
}

matrix4 operator*(const matrix4 &m1, const matrix4 &m2)
{
    matrix4 r;
    size_t i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            r[j][i] = 0.0f;
            for (k = 0; k < 4; k++)
                r[j][i] += m1[k][i] * m2[j][k];
        }
    }
    return r;
}

vec4 operator*(const matrix4 &m, const vec4 &v)
{
    vec4 r = {0.0f, 0.0f, 0.0f, 0.0f};
    size_t i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            r.v[i] += m[j][i] * v.v[j];
    }

    return r;
}

vec3 operator*(const matrix4 &m, vec3 &v)
{
    return (m * vec4(v, 1.0f)).xyz();
}

GLfloat *operator&(matrix4 &m)
{
    return (GLfloat *)&m.m;
}

const GLfloat *operator&(const matrix4 &m)
{
    return (const GLfloat *)&m.m;
}


#endif  // MATRIX_H
