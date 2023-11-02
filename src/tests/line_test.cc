/*
 * Filename: line_test.cc
 * Created on: June  5, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cmath>

#include "doctest.h"
#include "line.h"
#include "point.h"

TEST_CASE("Overload operador de igualdade")
{
    geom::Line<double_t, 2> r1(geom::Point<double_t, 2>({1, 1}),
                               geom::Point<double_t, 2>({4, 4}));

    geom::Line<double_t, 2> r2(geom::Point<double_t, 2>({1, 2}),
                               geom::Point<double_t, 2>({3, 4}));

    geom::Line<double_t, 2> r3(geom::Point<double_t, 2>({1, 1}),
                               geom::Point<double_t, 2>({4, 4}));

    SUBCASE("Pontos iguais")
    {
        CHECK(r1 == r3);
        CHECK(r3 == r1);
    }

    SUBCASE("Pontos diferentes") { CHECK(not(r1 == r2)); }
}
