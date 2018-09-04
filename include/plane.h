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

#ifndef PLANE_H
#define PLANE_H

#include "triangle.h"

struct plane3
{
    vec3 n;
    GLfloat d;

    plane3(void) {}

    plane3(const triangle3 &triangle)
    {
        n = Unit(Cross(triangle[1] - triangle[0], triangle[2] - triangle[0]));
        d = -Dot(triangle[0], n);
    }
};


GLfloat Distance(const vec3 &point, const plane3 &plane)
{
    return Dot(plane.n, point) + plane.d;
}

vec3 Projection(const vec3 &point, const plane3 &plane)
{
    return point - Distance(point, plane) * plane.n;
}


#endif  // PLANE_H
