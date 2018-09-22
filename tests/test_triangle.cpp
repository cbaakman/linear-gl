#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMatrix
#include <boost/test/unit_test.hpp>

#include "triangle.h"
#include "plane.h"


using namespace LinearGL;

BOOST_AUTO_TEST_CASE(in_triangle_test)
{
    vec3 triangle[] = {
        {-1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f}
    };

    vec3 point = {0.0f, 0.5f, 0.0f};

    BOOST_CHECK(PointInsideTriangle(triangle, point));
}

BOOST_AUTO_TEST_CASE(projection_test)
{
    vec3 triangle[] = {
        {-1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f}
    };

    vec3 point = {0.0f, 1.0f, 0.5f};

    plane3 plane(triangle);

    vec3 projection = Projection(point, plane);

    BOOST_CHECK(PointInsideTriangle(triangle, projection));
}
