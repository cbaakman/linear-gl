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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec.h"


namespace LinearGL
{
    typedef vec3 triangle3[3];

    bool PointInsideTriangle(const triangle3 &, const vec3 &point);
    bool PointInsideTriangle(const vec3 &trianglePoint0,
                             const vec3 &trianglePoint1,
                             const vec3 &trianglePoint2, const vec3 &point);
}

#endif  // TRIANGLE_H
