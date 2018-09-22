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

#include "quat.h"


namespace LinearGL
{
    quaternion Conjugate(const quaternion &q)
    {
        return {-q.x, -q.y, -q.z, q.w};
    }

    quaternion Inverse(const quaternion &q)
    {
        return Conjugate(q) / Length2(q);
    }

    quaternion Rotation(const vec3 &from, const vec3 &to)
    {
        GLfloat dot = Dot(Unit(from), Unit(to)),
                a, w;
        vec3 axis;

        if (dot < -0.99999999)
        {
            /*
                We can't calculate the axis if the vectors are in opposite directions.
                So take an arbitrary orthogonal axis.
                If the vectors are parallel, we won't need the axis.
             */

            if (std::abs(to.x) > std::abs(to.z))

                axis = vec3(-to.y, -to.x, 0.0f);
            else
                axis = vec3(0.0f, to.z, to.y);

            axis = Unit(axis);
            w = 0.0f;
        }
        else
        {
            a = acos(dot) / 2;
            w = cos(a);

            axis = sin(a) * Unit(Cross(from, to));
        }

        return {axis.x, axis.y, axis.z, w};
    }

    quaternion Slerp(const quaternion &start, const quaternion &end, GLfloat s)
    {
        quaternion startU = Unit(start),
                   endU = Unit(end);

        GLfloat w1, w2, theta, sTheta,

                dot = Dot(startU, endU);

        if (dot < 0.0f)
        {
            // assure shortest path (<= 180 degrees)
            startU = -startU;
            dot = Dot(startU, endU);
        }

        if (dot > 0.9995)  // too similar
        {
            w1 = 1.0f - s;
            w2 = s;
        }
        else
        {
            theta = acos(dot),
            sTheta = sin(theta);

            w1 = sin((1.0f - s) * theta) / sTheta;
            w2 = sin(s * theta) / sTheta;
        }

        return startU * w1 + endU * w2;
    }

    vec4 Rotate(const quaternion &rotation, const vec4 &v)
    {
        return Cross(Cross(rotation, v), Inverse(rotation));
    }

    vec3 Rotate(const quaternion &rotation, const vec3 &v)
    {
        return Rotate(rotation, vec4(v, 0.0f)).xyz();
    }

    quaternion FromAxisAngle(const vec3 &axis, const GLfloat angle)
    {
        vec3 a = Unit(axis);

        return {a.x * sin(angle / 2),
                a.y * sin(angle / 2),
                a.z * sin(angle / 2),
                cos(angle / 2)};
    }

    std::tuple<vec3, GLfloat> ToAxisAngle(const quaternion &q)
    {
        GLfloat angle = 2 * acos(q.w);
        vec3 axis = {q.x, q.y, q.z};
        axis = Unit(axis);

        return std::make_tuple(axis, angle);
    }

    const quaternion QUATERNION_ID = {0.0f, 0.0f, 0.0f, 1.0f};
}
