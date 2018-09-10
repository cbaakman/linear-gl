#include <math.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMatrix
#include <boost/test/unit_test.hpp>

#include "quat.h"


using namespace LinearGL;

BOOST_AUTO_TEST_CASE(test_slerp)
{
    vec3 v = {1.0f, 0.0f, 0.0f};

    // Rotate around z-axis, from 0 to 180 degrees.
    quaternion q0 = {0.0f, 0.0f, 0.0f, 1.0f},
               q1 = {0.0f, 0.0f, 1.0f, 0.0f};

    // Mid should be 90 degrees.
    GLfloat sqrtHalf = sqrt(0.5);
    quaternion mid = Slerp(q0, q1, 0.5f),
               cmp = {0.0f, 0.0f, sqrtHalf, sqrtHalf};

    BOOST_CHECK_EQUAL(mid, cmp);
}

BOOST_AUTO_TEST_CASE(test_rotate)
{
    vec3 v = {1.0f, 0.0f, 0.0f};

    // Rotate by 90 degrees around z-axis.
    GLfloat sqrtHalf = sqrt(0.5);
    quaternion q = {0.0f, 0.0f, sqrtHalf, sqrtHalf};

    vec3 r = Rotate(q, v),
         c = {0.0f, 1.0f, 0.0f};

    BOOST_CHECK_EQUAL(r, c);
}

BOOST_AUTO_TEST_CASE(test_get_rotation)
{
    // 90 degrees rotation around z-axis.
    vec3 from = {1.0f, 0.0f, 0.0f},
         to = {0.0f, 1.0f, 0.0f};

    GLfloat sqrtHalf = sqrt(0.5);
    quaternion r = Rotation(from, to),
               e = {0.0f, 0.0f, sqrtHalf, sqrtHalf};

    BOOST_CHECK_EQUAL(r, e);
}
