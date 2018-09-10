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

#ifndef QUAT_H
#define QUAT_H

#include "vec.h"

namespace LinearGL
{
    typedef vec4 quaternion;

    quaternion Conjugate(const quaternion &);

    quaternion Inverse(const quaternion &);

    quaternion Rotation(const vec3 &from, const vec3 &to);

    quaternion Slerp(const quaternion &start, const quaternion &end, GLfloat s);

    vec4 Rotate(const quaternion &rotation, const vec4 &);

    vec3 Rotate(const quaternion &rotation, const vec3 &);
}

#endif  // QUAT_H
