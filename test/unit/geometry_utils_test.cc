/*
 * Filename: geometry_utils.cc
 * Created on: June  8, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <cmath>

#include "convex_hull.h"
#include "point.h"
#include "vector.h"

#define EPSILON 10e-4

TEST_CASE("Encontrar o sentido no qual um vetor se encontra")
{
    geom::Point<double_t, 2> ref({ 12, 2 });
    geom::Point<double_t, 2> a({ 16, 6 });
    geom::Point<double_t, 2> b({ 16, -2 });
    geom::Point<double_t, 2> c({ 22, 2 });
    geom::Point<double_t, 2> d({ 30, 2 });

    SUBCASE("Sentido horário")
    {
        CHECK(geom::PointOrientation::ANTICLOCKWISE ==
              geom::Utils<double_t, 2>::Clockwise(ref, b, c));
    }

    SUBCASE("Sentido anti-horário")
    {
        CHECK(geom::PointOrientation::CLOCKWISE ==
              geom::Utils<double_t, 2>::Clockwise(ref, a, c));
    }

    SUBCASE("Pontos colineares")
    {
        CHECK(geom::PointOrientation::COLLINEAR ==
              geom::Utils<double_t, 2>::Clockwise(ref, d, c));
    }
}

TEST_CASE("Distância entre dois pontos")
{
    geom::Point<double_t, 2> a({ 6, 2 });
    geom::Point<double_t, 2> b({ 16, 0 });
    geom::Point<double_t, 2> c({ -2, -4 });
    geom::Point<double_t, 2> d({ -2, 8 });

    CHECK(geom::Utils<double_t, 2>::Distance(a, b) - 10.2 < EPSILON);
    CHECK(geom::Utils<double_t, 2>::Distance(a, c) - 10 < EPSILON);
    CHECK(geom::Utils<double_t, 2>::Distance(a, d) - 10 < EPSILON);
}

TEST_CASE("Ângulo polar de um ponto")
{
    // primeiro e segundo quadrante
    geom::Point<double_t, 2> a({ 18, 0 });
    geom::Point<double_t, 2> b({ 28, 0 });
    geom::Point<double_t, 2> c({ 28, 6 });
    geom::Point<double_t, 2> d({ 18, 10 });
    geom::Point<double_t, 2> e({ 8, 6 });
    geom::Point<double_t, 2> f({ 8, 0 });

    // terceiro e quarto quadrante
    geom::Point<double_t, 2> g({ 8, -6 });
    geom::Point<double_t, 2> h({ 18, -10 });
    geom::Point<double_t, 2> i({ 28, -6 });

    SUBCASE("Pontos no primeiro e segundo quadrante")
    {
        CHECK(geom::Utils<double_t, 2>::PolarAngle(a, b) == 0); // 0°
                                                                //
        CHECK((geom::Utils<double_t, 2>::PolarAngle(a, c) - (30.96 * PI / 180)) <
              EPSILON); // 30.96°
                        //
        CHECK((geom::Utils<double_t, 2>::PolarAngle(a, d) - PI / 2) < EPSILON); // 90°

        CHECK((geom::Utils<double_t, 2>::PolarAngle(a, e) - (149.04 * PI / 180)) <
              EPSILON); // 149.04°

        CHECK(geom::Utils<double_t, 2>::PolarAngle(a, f) == PI); // 180°
    }

    SUBCASE("Pontos no terceiro e quarto quadrante")
    {
        CHECK((geom::Utils<double_t, 2>::PolarAngle(a, g) - (210.96 * PI / 180)) <
              EPSILON); // 210.96°

        CHECK((geom::Utils<double_t, 2>::PolarAngle(a, h) - (3 * PI / 2)) <
              EPSILON); // 270°

        CHECK((geom::Utils<double_t, 2>::PolarAngle(a, i) - (329.04 * PI / 180)) <
              EPSILON); // 329.04°
    }
}

TEST_CASE("Conjunto de pontos é um polígono válido")
{
    Vector<geom::Point<double_t, 2>> points;

    points.PushBack(geom::Point<double_t, 2>({ 5, 2 }));
    points.PushBack(geom::Point<double_t, 2>({ 4, 1 }));

    SUBCASE("Uma reta") { CHECK(not geom::Utils<double_t, 2>::IsPolygon(points)); }

    points.PushBack(geom::Point<double_t, 2>({ 6, 3 }));
    SUBCASE("Três pontos colineares")
    {
        CHECK(not geom::Utils<double_t, 2>::IsPolygon(points));
    }

    points.PushBack(geom::Point<double_t, 2>({ 3, 0 }));
    SUBCASE("Quatro pontos colineares")
    {
        CHECK(not geom::Utils<double_t, 2>::IsPolygon(points));
    }

    points.PushBack(geom::Point<double_t, 2>({ 2, 1 }));
    SUBCASE("Um polígono") { CHECK(geom::Utils<double_t, 2>::IsPolygon(points)); }
}
