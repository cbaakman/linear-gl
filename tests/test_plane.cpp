#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMatrix
#include <boost/test/unit_test.hpp>

#include "plane.h"


using namespace LinearGL;

BOOST_AUTO_TEST_CASE(plane_equation_test)
{
    // Horizontal plane, through y = 1.0
    plane3 plane = {0.0f, 1.0f, 0.0f, -1.0f};

    // Point on plane.
    vec3 p = {-1.0f, 1.0f, 2.0f};

    GLfloat r = plane.equation[0] * p[0]
              + plane.equation[1] * p[1]
              + plane.equation[2] * p[2]
              + plane.equation[3];

    BOOST_CHECK_EQUAL(r, 0.0f);
}

BOOST_AUTO_TEST_CASE(reference_test)
{
    plane3 plane = {1.0f, 0.5f, 2.4f, -1.1f};

    GLfloat *ref = &plane;

    size_t i;
    for(i = 0; i < 4; i++)
        BOOST_CHECK_EQUAL(ref[i], plane[i]);
}
