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

#include <math.h>

#include "matrix.h"


namespace LinearGL
{
    template <size_t N>
    GLfloat *matrix<N>::operator[] (const size_t column)
    {
        return elements[column];
    }

    template <size_t N>
    const GLfloat *matrix<N>::operator[] (const size_t column) const
    {
        return elements[column];
    }

    template struct matrix<2>;
    template struct matrix<3>;
    template struct matrix<4>;


    template <size_t N>
    bool operator==(const matrix<N> &m1, const matrix<N> &m2)
    {
        size_t i, j;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                if (m1[i][j] != m2[i][j])
                    return false;

        return true;
    }

    template bool operator==(const matrix<2> &, const matrix<2> &);
    template bool operator==(const matrix<3> &, const matrix<3> &);
    template bool operator==(const matrix<4> &, const matrix<4> &);


    template <size_t N>
    bool operator!=(const matrix<N> &m1, const matrix<N> &m2)
    {
        size_t i, j;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                if (m1[i][j] != m2[i][j])
                    return true;

        return false;
    }

    template bool operator!=(const matrix<2> &, const matrix<2> &);
    template bool operator!=(const matrix<3> &, const matrix<3> &);
    template bool operator!=(const matrix<4> &, const matrix<4> &);


    template <size_t N>
    std::ostream &operator<<(std::ostream &os, const matrix<N> &m)
    {
        size_t i, j;
        for (i = 0; i < N; i++)
        {
            os << std::endl;

            os << "|";
            for (j = 0; j < N; j++)
            {
                if (j > 0)
                    os << ", ";
                os << m[j][i];
            }
            os << "|";
        }
        os << std::endl;

        return os;
    }

    template std::ostream &operator<<(std::ostream &, const matrix<2> &);
    template std::ostream &operator<<(std::ostream &, const matrix<3> &);
    template std::ostream &operator<<(std::ostream &, const matrix<4> &);


    template<size_t N>
    matrix<N - 1> ExcludeFrom(const matrix<N> &m, const size_t column, const size_t row)
    {
        matrix<N - 1> ex;

        size_t i, j, ki, kj;
        for (i = 0, ki = 0; ki < (N - 1); i++, ki++)
        {
            if (i == column)
                i++;

            for (j = 0, kj = 0; kj < (N - 1); j++, kj++)
            {
                if (j == row)
                    j++;

                ex[ki][kj] = m[i][j];
            }
        }
        return ex;
    }


    GLfloat Determinant(const matrix<2> &m)
    {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    template <size_t N>
    GLfloat Determinant(const matrix<N> &m)
    {
        size_t i;
        GLfloat det = 0.0f,
                a;
        for (i = 0; i < N; i++)
        {
            a = m[i][0] * Determinant(ExcludeFrom(m, i, 0));

            if (i % 2 == 0)
                det += a;
            else
                det -= a;
        }

        return det;
    }

    template GLfloat Determinant(const matrix<3> &);
    template GLfloat Determinant(const matrix<4> &);


    /**
     * source: http://semath.info/src/inverse-cofactor-ex4.html
     */
    template <size_t N>
    matrix<N> MatInverse(const matrix<N> &m)
    {
        matrix<N> adjugate;
        size_t i, j;
        GLfloat a;

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                a = Determinant(ExcludeFrom(m, j, i));

                if ((i + j) % 2 == 0)
                    adjugate[i][j] = a;
                else
                    adjugate[i][j] =-a;
            }
        }

        return adjugate / Determinant(m);
    }

    template <>
    matrix<2> MatInverse(const matrix<2> &m)
    {
        matrix<2> adjugate;
        adjugate[0][0] = m[1][1]; adjugate[1][0] =-m[1][0];
        adjugate[0][1] =-m[0][1]; adjugate[1][1] = m[0][0];

        return adjugate / Determinant(m);
    }

    template matrix<3> MatInverse(const matrix<3> &);
    template matrix<4> MatInverse(const matrix<4> &);


    template <size_t N>
    matrix<N> MatTranspose(const matrix<N> &m)
    {
        matrix<N> t;
        size_t i, j;
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                t[i][j] = m[j][i];
        return t;
    }

    template matrix<2> MatTranspose(const matrix<2> &);
    template matrix<3> MatTranspose(const matrix<3> &);
    template matrix<4> MatTranspose(const matrix<4> &);


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

    matrix4 MatRotAxis(const vec3 &axis, float angle)
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

    matrix4 MatQuat(const quaternion &q)
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
    /**
     * source: https://en.wikipedia.org/wiki/Transformation_matrix#Reflection_2
     */
    matrix4 MatReflect(const plane3 &plane)
    {
        matrix4 o;

        o[0][0] = 1.0f - 2 * plane[0] * plane[0];
        o[0][1] =       -2 * plane[1] * plane[0];
        o[0][2] =       -2 * plane[2] * plane[0];
        o[0][3] = 0.0f;

        o[1][0] =       -2 * plane[0] * plane[1];
        o[1][1] = 1.0f - 2 * plane[1] * plane[1];
        o[1][2] =       -2 * plane[2] * plane[1];
        o[1][3] = 0.0f;

        o[2][0] =       -2 * plane[0] * plane[2];
        o[2][1] =       -2 * plane[1] * plane[2];
        o[2][2] = 1.0f - 2 * plane[2] * plane[2];
        o[2][3] = 0.0f;

        o[3][0] =       -2 * plane[0] * plane[3];
        o[3][1] =       -2 * plane[1] * plane[3];
        o[3][2] =       -2 * plane[2] * plane[3];
        o[3][3] = 1.0f;

        return o;
    }

    matrix4 MatScale(const GLfloat s)
    {
        return MatScale(s, s, s);
    }

    matrix4 MatScale(const GLfloat sx, const GLfloat sy, const GLfloat sz)
    {
        matrix4 m = MatID();

        m[0][0] = sx;
        m[1][1] = sy;
        m[2][2] = sz;

        return m;
    }


    template <size_t N>
    matrix<N> operator*(const matrix<N> &m1, const matrix<N> &m2)
    {
        matrix<N> r;
        size_t i, j, k;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                r[j][i] = 0.0f;
                for (k = 0; k < N; k++)
                    r[j][i] += m1[k][i] * m2[j][k];
            }
        }
        return r;
    }

    template matrix<2> operator*(const matrix<2> &, const matrix<2> &);
    template matrix<3> operator*(const matrix<3> &, const matrix<3> &);
    template matrix<4> operator*(const matrix<4> &, const matrix<4> &);


    template <size_t N>
    matrix<N> operator*(const matrix<N> &m, const GLfloat f)
    {
        matrix<N> r;
        size_t i, j;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                r[i][j] = m[i][j] * f;
        return r;
    }

    template matrix<2> operator*(const matrix<2> &, const GLfloat);
    template matrix<3> operator*(const matrix<3> &, const GLfloat);
    template matrix<4> operator*(const matrix<4> &, const GLfloat);


    template <size_t N>
    matrix<N> operator*(const GLfloat f, const matrix<N> &m)
    {
        return m * f;
    }

    template matrix<2> operator*(const GLfloat, const matrix<2> &);
    template matrix<3> operator*(const GLfloat, const matrix<3> &);
    template matrix<4> operator*(const GLfloat, const matrix<4> &);


    template <size_t N>
    matrix<N> operator/(const matrix<N> &m, const GLfloat f)
    {
        matrix<N> r;
        size_t i, j;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                r[i][j] = m[i][j] / f;
        return r;
    }

    template matrix<2> operator/(const matrix<2> &, const GLfloat);
    template matrix<3> operator/(const matrix<3> &, const GLfloat);
    template matrix<4> operator/(const matrix<4> &, const GLfloat);


    template <size_t N>
    matrix<N> &operator*=(matrix<N> &m, const GLfloat f)
    {
        size_t i, j;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                m[i][j] *= f;
        return m;
    }

    template matrix<2> &operator*=(matrix<2> &, const GLfloat);
    template matrix<3> &operator*=(matrix<3> &, const GLfloat);
    template matrix<4> &operator*=(matrix<4> &, const GLfloat);


    template <size_t N>
    matrix<N> &operator/=(matrix<N> &m, const GLfloat f)
    {
        size_t i, j;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                m[i][j] /= f;
        return m;
    }

    template matrix<2> &operator/=(matrix<2> &, const GLfloat);
    template matrix<3> &operator/=(matrix<3> &, const GLfloat);
    template matrix<4> &operator/=(matrix<4> &, const GLfloat);


    vec4 operator*(const matrix4 &m, const vec4 &v)
    {
        vec4 r = {0.0f, 0.0f, 0.0f, 0.0f};
        size_t i, j;

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
                r[i] += m[j][i] * v[j];
        }

        return r;
    }

    vec3 operator*(const matrix4 &m, vec3 &v)
    {
        return (m * vec4(v, 1.0f)).xyz();
    }

    GLfloat *operator&(matrix4 &m)
    {
        return (GLfloat *)(m.elements);
    }

    const GLfloat *operator&(const matrix4 &m)
    {
        return (const GLfloat *)(m.elements);
    }
}
