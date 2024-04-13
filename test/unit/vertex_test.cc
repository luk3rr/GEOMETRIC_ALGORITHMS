/*
 * Filename: vertex_test.cc
 * Created on: November  2, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <cmath>

#include "vertex.h"
#include "edge.h"

TEST_CASE("CreateVertex")
{
    SUBCASE("Create Vertex with default values")
    {
        graph::Vertex<int32_t, double_t> vertex;
        CHECK(vertex.GetID() == 0);
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
    graph::Vertex<int32_t, double_t> vertex;
    graph::Vertex<int32_t, double_t> vertex1;
    graph::Vertex<int32_t, double_t> vertex2;

    SUBCASE("Set ID, CurrentCost, and Edge2Predecessor")
    {
        vertex.SetID(2);
        vertex.SetCurrentCost(10);

        graph::Edge<int32_t, double_t> edge(&vertex1, &vertex2);

        vertex.SetEdge2Predecessor(&edge);

        CHECK(vertex.GetID() == 2);
        CHECK(vertex.GetCurrentCost() == 10);
        CHECK(vertex.GetEdge2Predecessor() == &edge);
    }
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
