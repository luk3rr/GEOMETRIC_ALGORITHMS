/*
 * Filename: point_test.cc
 * Created on: June  5, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <cmath>

#include "point.h"

TEST_CASE("Overload operador de igualdade")
{
    geom::Point<double_t, 2> A({ 1, 5 });
    geom::Point<double_t, 2> B({ 1, 3 });
    geom::Point<double_t, 2> C({ 1, 5 });

    SUBCASE("Pontos iguais")
    {
        CHECK(A == C);
        CHECK(C == A);
    }

    SUBCASE("Pontos diferentes")
    {
        CHECK(not(A == B));
    }
}

// TODO: Definir se o operador de overload será implementado ou comparador
// customizado
//       será utilizado (template)
// TEST_CASE("Overload operador menor")
//{
//    geom::Point<double_t, 2> A(1, 5);
//    geom::Point<double_t, 2> B(1, 3);
//    geom::Point<double_t, 2> C(1, 5);
//    geom::Point<double_t, 2> D(2, -1);
//    geom::Point<double_t, 2> E(-1, -1);
//
//    SUBCASE("Pontos iguais")
//    {
//        CHECK(not (A < C));
//    }
//
//    SUBCASE("Pontos diferentes")
//    {
//        CHECK(not (A < B));
//        CHECK(D < B);
//        CHECK(E < D);
//    }
//}
//
// TEST_CASE("Overload operador menor ou igual") {
//    geom::Point<double_t, 2> A = geom::Point<double_t, 2>(1, 5);
//    geom::Point<double_t, 2> B = geom::Point<double_t, 2>(1, 3);
//    geom::Point<double_t, 2> C = geom::Point<double_t, 2>(1, 5);
//    geom::Point<double_t, 2> D = geom::Point<double_t, 2>(2, -1);
//    geom::Point<double_t, 2> E = geom::Point<double_t, 2>(-1, -1);
//
//    SUBCASE("Pontos iguais") {
//        CHECK(A <= C);
//    }
//
//    SUBCASE("Pontos diferentes") {
//        CHECK(!(A <= B));
//        CHECK(D <= B);
//        CHECK(E <= D);
//    }
//}
