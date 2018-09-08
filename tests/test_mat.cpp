#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMatrix
#include <boost/test/unit_test.hpp>

#include "matrix.h"


BOOST_AUTO_TEST_CASE(skew_test)
{
    // Horizontal plane at y = 0.5.
    plane3 plane;
    plane.n = {0.0f, 1.0f, 0.0f};
    plane.d = -0.5f;
    matrix4 ms = MatSkew(plane);

    vec3 p = {1.0f, 1.0f, 1.0f},
         r = ms * p,
         c = {1.0f, 0.0f, 1.0f};

    BOOST_CHECK_EQUAL(c, r);
}

BOOST_AUTO_TEST_CASE(inverse_test)
{
    vec3 axis = {1.0f, -1.0f, 0.5f};
    matrix4 mr, mc,
            mi = MatID();

    // Create an invertible matrix.
    quaternion q = {1.0f, 0.0f, 0.0f, 1.0f};
    mr = MatQuat(q) * MatTranslate(axis) * MatScale(2.0f);

    mc = MatInverse(mr) * mr;

    vec3 v = {1.0f, -1.0f, 0.5f},
         r = mi * v;

    BOOST_CHECK_EQUAL(mc, mi);
    BOOST_CHECK_EQUAL(v, r);
}

BOOST_AUTO_TEST_CASE(rotate_test)
{
    // Rotate 90 degrees around x-axis.
    quaternion q = {1.0f, 0.0f, 0.0f, 1.0f};
    matrix4 rot = MatQuat(q);

    vec3 v = {0.0f, 1.0f, 0.0f},
         r = rot * v,
         c = {0.0f, 0.0f, 1.0f};

    BOOST_CHECK_EQUAL(r, c);
}

BOOST_AUTO_TEST_CASE(translate_test)
{
    vec3 t = {0.0f, 0.0f, -1.0f};
    matrix4 tr = MatTranslate(t);

    vec3 v = {1.0f, 0.0f, 0.0f},
         r = tr * v,
         c = v + t;

    BOOST_CHECK_EQUAL(r, c);
}

BOOST_AUTO_TEST_CASE(scale_test)
{
    vec3 v = {1.0f, -1.0f, 0.5f};

    matrix4 sc = MatScale(2.0f, 0.5f, 4.0f);

    vec3 r = sc * v,
         c = {2.0f, -0.5f, 2.0f};

    BOOST_CHECK_EQUAL(r, c);
}
