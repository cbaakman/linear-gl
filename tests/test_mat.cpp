#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMatrix
#include <boost/test/unit_test.hpp>

#include "matrix.h"


BOOST_AUTO_TEST_CASE(inverse_test)
{
    vec3 axis = {0.0f, 1.0f, 0.0f};
    matrix4 m = MatRotAxis(axis, PI/2);

    vec3 v = {1.0f, -1.0f, 0.5f},
         r = MatInverse(m) * m * v;

    BOOST_CHECK_EQUAL(v, r);
}

BOOST_AUTO_TEST_CASE(rotate_test)
{
    vec3 axis = {1.0f, 0.0f, 0.0f};
    matrix4 rot = MatRotAxis(axis, PI/2);

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
