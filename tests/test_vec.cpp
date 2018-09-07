#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMatrix
#include <boost/test/unit_test.hpp>

#include "vec.h"


BOOST_AUTO_TEST_CASE(add_on_test)
{
    vec3 v1 = {1.0f, -1.0f, 0.5f},
         v2 = {-1.0f, 0.0f, 0.5f},
         r1 = v1 + v2,
         c1 = {0.0f, -1.0f, 1.0f},
         r2 = v1 - v2,
         c2 = {2.0f, -1.0f, 0.0f};

    BOOST_CHECK_EQUAL(r1, c1);
    BOOST_CHECK_EQUAL(r2, c2);
}

BOOST_AUTO_TEST_CASE(mult_test)
{
    GLfloat f = 2.0f;
    vec3 v = {1.0f, -1.0f, 0.5f},
         r1 = v * f,
         c1 = {2.0f, -2.0f, 1.0f},
         r2 = v / f,
         c2 = {0.5f, -0.5f, 0.25f};

    BOOST_CHECK_EQUAL(r1, c1);
    BOOST_CHECK_EQUAL(r2, c2);
}

BOOST_AUTO_TEST_CASE(length_test)
{
    vec3 v = {1.0f, -1.0f, 0.5f},
         r = Unit(v);

    BOOST_CHECK_EQUAL(Length(r), 1.0f);
}

BOOST_AUTO_TEST_CASE(cross_test)
{
    vec3 a = {0.0f, 0.0f, 1.0f},
         b = {1.0f, 0.0f, 0.0f},
         axb = Cross(a, b),
         bxa = Cross(b, a);

    BOOST_CHECK(axb.y > 0.0f);
    BOOST_CHECK(bxa.y < 0.0f);
}