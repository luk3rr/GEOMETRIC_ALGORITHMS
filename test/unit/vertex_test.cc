/*
 * Filename: vertex_test.cc
 * Created on: November  2, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <cmath>

#include "edge.h"
#include "vertex.h"

TEST_CASE("CreateVertex")
{
    SUBCASE("Create Vertex with default values")
    {
        graph::Vertex<int32_t, double_t> vertex;
        CHECK(vertex.GetCurrentCost() == 0);
        CHECK(vertex.GetEdge2Predecessor() == nullptr);
        CHECK(vertex.GetAdjacencyList().Size() == 0);
    }

    SUBCASE("Create Vertex with specified ID")
    {
        graph::Vertex<int32_t, double_t> vertex(1);
        CHECK(vertex.GetID() == 1);
        CHECK(vertex.GetCurrentCost() == 0);
        CHECK(vertex.GetEdge2Predecessor() == nullptr);
        CHECK(vertex.GetAdjacencyList().Size() == 0);
    }
}

TEST_CASE("SetVertexAttributes")
{
    graph::Vertex<int32_t, double_t> vertex0;
    graph::Vertex<int32_t, double_t> vertex1;
    graph::Vertex<int32_t, double_t> vertex2;

    vertex0.SetCurrentCost(10);

    graph::Edge<int32_t, double_t> edge(0, &vertex1, &vertex2);

    vertex0.SetEdge2Predecessor(&edge);

    CHECK(vertex0.GetID() == 0);
    CHECK(vertex0.GetCurrentCost() == 10);
    CHECK(vertex0.GetEdge2Predecessor() == &edge);
}

TEST_CASE("CompareVertices")
{
    graph::Vertex<int32_t, double_t> vertex1;
    graph::Vertex<int32_t, double_t> vertex2;

    SUBCASE("Compare vertices based on current cost")
    {
        vertex1.SetCurrentCost(5);
        vertex2.SetCurrentCost(10);

        CHECK(vertex1 < vertex2);
        CHECK(vertex1 <= vertex2);
        CHECK(vertex2 > vertex1);
        CHECK(vertex2 >= vertex1);
        CHECK(vertex1 == vertex1);
        CHECK_FALSE(vertex1 == vertex2);
    }
}
