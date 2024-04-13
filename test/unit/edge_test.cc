/*
 * Filename: edge_test.cc
 * Created on: November  2, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <cmath>

#include "edge.h"
#include "pair.h"
#include "vertex.h"

TEST_CASE("Test graph::Edge class construction and basic operations")
{
    // Create vertices
    graph::Vertex<double_t, double_t> vertexA({ 0.0, 0.0 }, 0);
    graph::Vertex<double_t, double_t> vertexB({ 1.0, 1.0 }, 1);

    // Create an edge with default cost
    graph::Edge<double_t, double_t> edgeAB(&vertexA, &vertexB);

    CHECK(edgeAB.GetA() == &vertexA);
    CHECK(edgeAB.GetB() == &vertexB);

    CHECK(edgeAB.GetCost() == 0);

    // Create an edge with a specified cost
    graph::Edge<double_t, double_t> edgeBA(&vertexB, &vertexA, 10);
    CHECK(edgeBA.GetA() == &vertexB);
    CHECK(edgeBA.GetB() == &vertexA);
    CHECK(edgeBA.GetCost() == 10);

    // Test cost modification
    edgeAB.SetCost(5);
    CHECK(edgeAB.GetCost() == 5);
}

TEST_CASE("Test graph::Edge comparison")
{
    graph::Vertex<int32_t, double_t> vertexA({ 0.0, 0.0 }, 0);
    graph::Vertex<int32_t, double_t> vertexB({ 1.0, 1.0 }, 1);

    graph::Edge<int32_t, double_t> edgeAB(&vertexA, &vertexB);
    graph::Edge<int32_t, double_t> edgeBA(&vertexB, &vertexA, 10);

    CHECK(edgeAB < edgeBA); // Compare by cost
}

TEST_CASE("Test graph::Edge vertices extraction")
{
    graph::Vertex<int32_t, double_t> vertexA({ 0.0, 0.0 }, 0);
    graph::Vertex<int32_t, double_t> vertexB({ 1.0, 1.0 }, 1);

    graph::Edge<int32_t, double_t> edgeAB(&vertexA, &vertexB);

    Pair<graph::Vertex<int32_t, double_t>*, graph::Vertex<int32_t, double_t>*>
        vertices = edgeAB.GetVertices();

    CHECK(vertices.GetFirst() == &vertexA);
    CHECK(vertices.GetSecond() == &vertexB);
}

TEST_CASE("Test graph::Edge copy constructor and assignment operator")
{
    graph::Vertex<int32_t, double_t> vertexA({ 0.0, 0.0 }, 0);
    graph::Vertex<int32_t, double_t> vertexB({ 1.0, 1.0 }, 1);

    graph::Edge<int32_t, double_t> edgeAB(&vertexA, &vertexB);

    SUBCASE("Copy constructor")
    {
        graph::Edge<int32_t, double_t> edgeCopy(edgeAB);
        CHECK(edgeCopy.GetA() == &vertexA);
        CHECK(edgeCopy.GetB() == &vertexB);
        CHECK(edgeCopy.GetCost() == 0);
    }

    SUBCASE("assignment operator")
    {
        graph::Edge<int32_t, double_t> edgeAssignment(&vertexB, &vertexA, 10);
        edgeAssignment = edgeAB;
        CHECK(edgeAssignment.GetA() == &vertexA);
        CHECK(edgeAssignment.GetB() == &vertexB);
        CHECK(edgeAssignment.GetCost() == 0);
    }
}
