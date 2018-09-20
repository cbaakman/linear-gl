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

#include "vec.h"


namespace LinearGL
{
    const double PI = acos(-1.0);


    GLfloat &vec<2>::operator[](const size_t i)
    {
        return coords[i];
    }
    GLfloat &vec<3>::operator[](const size_t i)
    {
        return coords[i];
    }
    GLfloat &vec<4>::operator[](const size_t i)
    {
        return coords[i];
    }


    const GLfloat &vec<2>::operator[](const size_t i) const
    {
        return coords[i];
    }
    const GLfloat &vec<3>::operator[](const size_t i) const
    {
        return coords[i];
    }
    const GLfloat &vec<4>::operator[](const size_t i) const
    {
        return coords[i];
    }


    vec<2>::vec(void)
    {
    }
    vec<3>::vec(void)
    {
    }
    vec<4>::vec(void)
    {
    }

    vec<2>::vec(const GLfloat _x, const GLfloat _y): x(_x), y(_y)
    {
    }


    vec<2> vec<3>::xy(void)
    {
        return {x, y};
    }


    vec<3>::vec(const GLfloat _x, const GLfloat _y, const GLfloat _z): x(_x), y(_y), z(_z)
    {
    }


    vec<3>::vec(const vec<2> &v, const GLfloat _z): x(v.x), y(v.y), z(_z)
    {
    }


    vec<3> vec<4>::xyz(void)
    {
        return {x, y, z};
    }


    vec<4>::vec(const GLfloat _x, const GLfloat _y, const GLfloat _z, const GLfloat _w): x(_x), y(_y), z(_z), w(_w)
    {
    }


    vec<4>::vec(const vec<3> &v, const GLfloat _w): x(v.x), y(v.y), z(v.z), w(_w)
    {
    }


    template <size_t N>
    vec<N> &operator+=(vec<N> &v1, const vec<N> &v2)
    {
        size_t i;
        for(i = 0; i < N; i++)
            v1[i] += v2[i];
        return v1;
    }

    template vec<2> &operator+=(vec<2> &, const vec<2> &);
    template vec<3> &operator+=(vec<3> &, const vec<3> &);
    template vec<4> &operator+=(vec<4> &, const vec<4> &);


    template <size_t N>
    vec<N> &operator-=(vec<N> &v1, const vec<N> &v2)
    {
        size_t i;
        for(i = 0; i < N; i++)
            v1[i] -= v2[i];
        return v1;
    }

    template vec<2> &operator-=(vec<2> &, const vec<2> &);
    template vec<3> &operator-=(vec<3> &, const vec<3> &);
    template vec<4> &operator-=(vec<4> &, const vec<4> &);


    template <size_t N>
    vec<N> operator+(const vec<N> &v1, const vec<N> &v2)
    {
        vec<N> sum;
        size_t i = 0;
        for (i = 0; i < N; i++)
            sum[i] = v1[i] + v2[i];
        return sum;
    }

    template vec<2> operator+(const vec<2> &, const vec<2> &);
    template vec<3> operator+(const vec<3> &, const vec<3> &);
    template vec<4> operator+(const vec<4> &, const vec<4> &);


    template <size_t N>
    vec<N> operator-(const vec<N> &v1, const vec<N> &v2)
    {
        vec<N> sub;
        size_t i = 0;
        for (i = 0; i < N; i++)
            sub[i] = v1[i] - v2[i];
        return sub;
    }

    template vec<2> operator-(const vec<2> &, const vec<2> &);
    template vec<3> operator-(const vec<3> &, const vec<3> &);
    template vec<4> operator-(const vec<4> &, const vec<4> &);


    template <size_t N>
    vec<N> operator-(const vec<N> &v)
    {
        vec<N> neg;
        size_t i = 0;
        for (i = 0; i < N; i++)
            neg[i] = -v[i];
        return neg;
    }

    template vec<2> operator-(const vec<2> &);
    template vec<3> operator-(const vec<3> &);
    template vec<4> operator-(const vec<4> &);


    template <size_t N>
    vec<N> operator*(const vec<N> &v, const GLfloat scalar)
    {
        vec<N> mul;
        size_t i = 0;
        for (i = 0; i < N; i++)
            mul[i] = v[i] * scalar;
        return mul;
    }

    template vec<2> operator*(const vec<2> &, const GLfloat);
    template vec<3> operator*(const vec<3> &, const GLfloat);
    template vec<4> operator*(const vec<4> &, const GLfloat);


    template <size_t N>
    vec<N> operator*(const GLfloat scalar, const vec<N> &v)
    {
        return v * scalar;
    }

    template vec<2> operator*(const GLfloat, const vec<2> &);
    template vec<3> operator*(const GLfloat, const vec<3> &);
    template vec<4> operator*(const GLfloat, const vec<4> &);


    template <size_t N>
    vec<N> operator/(const vec<N> &v, const GLfloat scalar)
    {
        vec<N> div;
        size_t i = 0;
        for (i = 0; i < N; i++)
            div[i] = v[i] / scalar;
        return div;
    }

    template vec<2> operator/(const vec<2> &, const GLfloat);
    template vec<3> operator/(const vec<3> &, const GLfloat);
    template vec<4> operator/(const vec<4> &, const GLfloat);


    template <size_t N>
    vec<N> &operator*=(vec<N> &v, const GLfloat scalar)
    {
        size_t i;
        for(i = 0; i < N; i++)
            v[i] *= scalar;
        return v;
    }

    template vec<2> &operator*=(vec<2> &, const GLfloat);
    template vec<3> &operator*=(vec<3> &, const GLfloat);
    template vec<4> &operator*=(vec<4> &, const GLfloat);


    template <size_t N>
    vec<N> &operator/=(vec<N> &v, const GLfloat scalar)
    {
        size_t i;
        for(i = 0; i < N; i++)
            v[i] /= scalar;
        return v;
    }

    template vec<2> &operator/=(vec<2> &, const GLfloat);
    template vec<3> &operator/=(vec<3> &, const GLfloat);
    template vec<4> &operator/=(vec<4> &, const GLfloat);


    template <size_t N>
    bool operator==(const vec<N> &v1, const vec<N> &v2)
    {
        size_t i = 0;
        for (i = 0; i < N; i++)
            if (v1[i] != v2[i])
                return false;

        return true;
    }

    template bool operator==(const vec<2> &, const vec<2> &);
    template bool operator==(const vec<3> &, const vec<3> &);
    template bool operator==(const vec<4> &, const vec<4> &);



    template <size_t N>
    bool operator!=(const vec<N> &v1, const vec<N> &v2)
    {
        size_t i = 0;
        for (i = 0; i < N; i++)
            if (v1[i] != v2[i])
                return true;

        return false;
    }

    template bool operator!=(const vec<2> &, const vec<2> &);
    template bool operator!=(const vec<3> &, const vec<3> &);
    template bool operator!=(const vec<4> &, const vec<4> &);


    template <size_t N>
    std::ostream& operator<<(std::ostream& os, const vec<N> v)
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

    template std::ostream& operator<<(std::ostream& os, const vec<2> v);
    template std::ostream& operator<<(std::ostream& os, const vec<3> v);
    template std::ostream& operator<<(std::ostream& os, const vec<4> v);


    template <size_t N>
    vec<N> Unit(const vec<N> &v)
    {
        return v / Length(v);
    }

    template vec<2> Unit(const vec<2> &);
    template vec<3> Unit(const vec<3> &);
    template vec<4> Unit(const vec<4> &);


    template <size_t N>
    GLfloat Length(const vec<N> &v)
    {
        return sqrt(Length2(v));
    }

    template GLfloat Length(const vec<2> &);
    template GLfloat Length(const vec<3> &);
    template GLfloat Length(const vec<4> &);


    template <size_t N>
    GLfloat Length2(const vec<N> &v)
    {
        GLfloat l2 = 0.0f;
        size_t i;
        for (i = 0; i < N; i++)
            l2 += v[i] * v[i];
        return l2;
    }

    template GLfloat Length2(const vec<2> &);
    template GLfloat Length2(const vec<3> &);
    template GLfloat Length2(const vec<4> &);


    template <size_t N>
    GLfloat Dot(const vec<N> &v1, const vec<N> &v2)
    {
        GLfloat r = 0.0f;
        size_t i;
        for (i = 0; i < N; i++)
            r += v1[i] * v2[i];
        return r;
    }

    template GLfloat Dot(const vec<2> &, const vec<2> &);
    template GLfloat Dot(const vec<3> &, const vec<3> &);
    template GLfloat Dot(const vec<4> &, const vec<4> &);


    template <size_t N>
    GLfloat Angle(const vec<N> &v1, const vec<N> &v2)
    {
        GLfloat dot = Dot(Unit(v1), Unit(v2));

        if (dot > 0.99999999)
            return 0.0f;
        else if (dot < -0.99999999)
            return PI;

        return acos(dot);
    }

    template GLfloat Angle(const vec<2> &, const vec<2> &);
    template GLfloat Angle(const vec<3> &, const vec<3> &);
    template GLfloat Angle(const vec<4> &, const vec<4> &);


    vec3 Cross(const vec3 &v1, const vec3 &v2)
    {
        return {v1.y * v2.z - v2.y * v1.z,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x};
    }


    vec4 Cross(const vec4 &v1, const vec4 &v2)
    {
        return {v1.y * v2.z - v1.z * v2.y + v1.x * v2.w + v1.w * v2.x,
                v1.z * v2.x - v1.x * v2.z + v1.y * v2.w + v1.w * v2.y,
                v1.x * v2.y - v1.y * v2.x + v1.z * v2.w + v1.w * v2.z,
                v1.w * v2.w - v1.x * v2.x - v1.y * v2.y - v1.z * v2.z};
    }
}
