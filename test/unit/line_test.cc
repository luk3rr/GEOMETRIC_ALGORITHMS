/*
 * Filename: line_test.cc
 * Created on: June  5, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <cmath>

#include "line.h"
#include "point.h"

TEST_CASE("Overload of equality operator")
{
    geom::Point<double_t, 2> point1a({ 1, 1 });
    geom::Point<double_t, 2> point1b({ 4, 4 });

    geom::Point<double_t, 2> point2a({ 1, 2 });
    geom::Point<double_t, 2> point2b({ 3, 4 });

    geom::Point<double_t, 2> point3a({ 1, 1 });
    geom::Point<double_t, 2> point3b({ 4, 4 });

    geom::Line<double_t, 2> line1(point1a, point1b);
    geom::Line<double_t, 2> line2(point2a, point2b);
    geom::Line<double_t, 2> line3(point3a, point3b);

    SUBCASE("Equal points")
    {
        CHECK(line1 == line3);
        CHECK(line3 == line1);
    }

    SUBCASE("Different points")
    {
        CHECK(not(line1 == line2));
    }
}

TEST_CASE("Test if a change in a Point attribute affects Line")
{
    geom::Point<double, 2> pointA({ 1.0, 2.0 });
    geom::Point<double, 2> pointB({ 3.0, 4.0 });

    geom::Line<double, 2> line(pointA, pointB);

    // Change attribute
    pointA.SetCoordinates({ 7, 10.0 });

    // Check effects
    CHECK(((line.GetA()->GetCoordinates().At(0) == 7) and
           (line.GetA()->GetCoordinates().At(1) == 10.0)));

    CHECK(((line.GetB()->GetCoordinates().At(0) == 3) and
           (line.GetB()->GetCoordinates().At(1) == 4)));
}
