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

#include "plane.h"


namespace LinearGL
{
    plane3::plane3(void)
    {
    }

    plane3::plane3(const GLfloat _a, const GLfloat _b, const GLfloat _c, const GLfloat _d)
    : a(_a), b(_b), c(_c), d(_d)
    {
    }

    plane3::plane3(const vec3 &n, const GLfloat d)
    {
        GLfloat nl = Length(n);
        equation[0] = n[0] / nl;
        equation[1] = n[1] / nl;
        equation[2] = n[2] / nl;
        equation[3] = d;
    }

    plane3::plane3(const vec3 &p0, const vec3 &p1, const vec3 &p2)
    {
        vec3 n = Unit(Cross(p1 - p0, p2 - p1));
        GLfloat d = -Dot(p0, n);

        equation[0] = n[0];
        equation[1] = n[1];
        equation[2] = n[2];
        equation[3] = d;
    }

    plane3::plane3(const triangle3 &triangle): plane3(triangle[0], triangle[1], triangle[2])
    {
    }

    GLfloat &plane3::operator[] (const size_t i)
    {
        return equation[i];
    }
    const GLfloat &plane3::operator[] (const size_t i) const
    {
        return equation[i];
    }

    vec3 plane3::normal(void) const
    {
        return vec3(equation[0], equation[1], equation[2]);
    }

    GLfloat *operator&(plane3 &plane)
    {
        return plane.equation;
    }

    const GLfloat *operator&(const plane3 &plane)
    {
        return plane.equation;
    }

    GLfloat Distance(const vec3 &point, const plane3 &plane)
    {
        return Dot(plane.normal(), point) + plane.d;
    }

    vec3 Projection(const vec3 &point, const plane3 &plane)
    {
        return point - Distance(point, plane) * plane.normal();
    }
}
