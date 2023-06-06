/*
* Filename: polygon_test.cc
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "doctest.h"
#include "polygon.h"

TEST_CASE("Inserção/remoção de pontos") {
    geom::Polygon polygon;

    polygon.InsertPoint(1, 2);
    polygon.InsertPoint(4, 6);
    polygon.InsertPoint(8, 10);
    polygon.InsertPoint(geom::Point2D(8, 10));
    polygon.InsertPoint(geom::Point2D(2, 3));

    REQUIRE(polygon.GetNumPoints() == 5);

    SUBCASE("Remoção de pontos") {
        REQUIRE(polygon.IsPointOnPolygon(1, 2));

        polygon.DeletePoint(1, 2);
        CHECK(!polygon.IsPointOnPolygon(1, 2));

        REQUIRE(polygon.IsPointOnPolygon(4, 6));

        polygon.DeletePoint(geom::Point2D(4, 6));
        CHECK(!polygon.IsPointOnPolygon(4, 6));
    }

    SUBCASE("Exclusão do polygon") {
        polygon.Delete();
        CHECK(polygon.GetNumPoints() == 0);
    }
}
