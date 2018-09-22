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

#include "triangle.h"


namespace LinearGL
{
    bool SameSide(const vec3 &linePoint1, const vec3 &linePoint2,
                  const vec3 &pointA, const vec3 &pointB)
    {
        vec3 cp1 = Cross(pointB - pointA, linePoint1 - pointA),
             cp2 = Cross(pointB - pointA, linePoint2 - pointA);

        // make it -0.00001f instead of 0.0f to cover up the error in floating point
        return (Dot(cp1, cp2) >= -0.00001f);
    }


    bool PointInsideTriangle(const triangle3 &triangle, const vec3 &point)
    {
        return PointInsideTriangle(triangle[0], triangle[1], triangle[2], point);
    }


    bool PointInsideTriangle(const vec3 &p0,
                             const vec3 &p1,
                             const vec3 &p2, const vec3 &point)
    {
        return (SameSide(point, p0, p1, p2) &&
                SameSide(point, p1, p0, p2) &&
                SameSide(point, p2, p0, p1));
    }
}
