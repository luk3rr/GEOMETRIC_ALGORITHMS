/*
 * Filename: heuristics_test.cc
 * Created on: April 11, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */
#include "doctest.h"

#include <cmath>

#include "heuristics.h"

constexpr double_t EPSILON = 1e-6;

TEST_CASE("Euclidian distance")
{
    graph::Vertex<double_t, double_t, 2> source({ 0, 0 }, 0);
    graph::Vertex<double_t, double_t, 2> target({ 3, 4 }, 1);

    double_t expected_distance = 5.0;

    double_t calculated_distance = heuristics::distance::Euclidean(&source, &target);
    CHECK(std::abs(calculated_distance - expected_distance) < EPSILON);
}

TEST_CASE("Manhattan distance")
{
    graph::Vertex<double_t, double_t, 2> source({ 0, 0 }, 0);
    graph::Vertex<double_t, double_t, 2> target({ 3, 4 }, 1);

    double_t expected_distance = 7.0;

    double_t calculated_distance = heuristics::distance::Manhattan(&source, &target);
    CHECK(std::abs(calculated_distance - expected_distance) < EPSILON);
}

TEST_CASE("Minkowski distance")
{
    graph::Vertex<double_t, double_t, 2> source({ 0, 0 }, 0);
    graph::Vertex<double_t, double_t, 2> target({ 3, 4 }, 1);

    double_t p                 = 2.0;
    double_t expected_distance = 5.0;

    double_t calculated_distance = heuristics::distance::Minkowski(&source, &target, p);
    CHECK(std::abs(calculated_distance - expected_distance) < EPSILON);
}

TEST_CASE("Hamming distance")
{
    graph::Vertex<uint32_t, uint32_t, 5> source({ 1, 0, 1, 1, 0 }, 0);
    graph::Vertex<uint32_t, uint32_t, 5> target({ 0, 0, 1, 0, 1 }, 1);

    double_t expected_distance = 3.0;

    double_t calculated_distance = heuristics::distance::Hamming(&source, &target);
    CHECK(std::abs(calculated_distance - expected_distance) < EPSILON);
}
