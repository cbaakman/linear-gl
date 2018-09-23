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


namespace LinearGL
{
    struct plane3
    {
        // Ax + By + Cz + D = 0
        union
        {
            GLfloat equation[4];
            struct { GLfloat a, b, c, d; };
        };

        plane3(void);
        plane3(const GLfloat a, const GLfloat b, const GLfloat c, const GLfloat d);
        plane3(const vec3 &normal, const GLfloat d);
        plane3(const triangle3 &);
        plane3(const vec3 &trianglePoint0,
               const vec3 &trianglePoint1,
               const vec3 &trianglePoint2);

        GLfloat &operator[] (const size_t i);
        const GLfloat &operator[] (const size_t i) const;

        vec3 normal(void) const;
    };

    GLfloat *operator&(plane3 &);
    const GLfloat *operator&(const plane3 &);

    GLfloat Distance(const vec3 &point, const plane3 &);

    vec3 Projection(const vec3 &point, const plane3 &);
}

#endif  // PLANE_H
