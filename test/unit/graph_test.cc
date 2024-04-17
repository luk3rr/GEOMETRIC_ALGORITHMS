/*
 * Filename: graph_test.cc
 * Created on: November  2, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <cmath>

#include "graph.h"

TEST_CASE("AddVertexAndEdge")
{
    graph::Graph<int32_t, double_t> undirectedGraph;

    undirectedGraph.AddVertex();
    undirectedGraph.AddVertex();
    undirectedGraph.AddVertex();

    REQUIRE(undirectedGraph.GetVertices().Size() == 3);
    REQUIRE(undirectedGraph.GetNumVertices() == 3);

    // Add an edge between vertex 0 and 1 with cost 10
    undirectedGraph.AddEdge(0, 1, 10);
    // Add an edge between vertex 1 and 2 with cost 20
    undirectedGraph.AddEdge(1, 2, 20);
    // Add an edge between vertex 2 and 0 with cost 30
    undirectedGraph.AddEdge(2, 0, 30);

    CHECK(undirectedGraph.GetEdges().Size() == 3);
}

TEST_CASE("Adding an edge to a vertex that does not exist")
{

    graph::Graph<int32_t, double_t> undirectedGraph;

    undirectedGraph.AddVertex();

    SUBCASE("(A,B), A does not exist")
    {
        CHECK_FALSE(undirectedGraph.AddEdge(20, 0));
    }

    SUBCASE("(A,B), B does not exist")
    {
        CHECK_FALSE(undirectedGraph.AddEdge(0, 20));
    }
}

TEST_CASE("Removing a vertex from the graph")
{
    graph::Graph<int32_t, double_t> undirectedGraph;

    undirectedGraph.AddVertex();

    SUBCASE("Removing an existing vertex")
    {
        REQUIRE(undirectedGraph.ContainsVertex(0));
        CHECK(undirectedGraph.RemoveVertex(0));
        CHECK_FALSE(undirectedGraph.ContainsVertex(0));
    }

    SUBCASE("Removing a non-existing vertex")
    {
        CHECK_FALSE(undirectedGraph.RemoveVertex(20));
    }
}

TEST_CASE("Removing an edge from the graph")
{
    graph::Graph<int32_t, double_t> undirectedGraph;

    undirectedGraph.AddVertex();
    undirectedGraph.AddVertex();

    undirectedGraph.AddEdge(0, 1);

   SUBCASE("Removing an existing edge")
   {
       REQUIRE(undirectedGraph.ContainsEdge(0));
       CHECK(undirectedGraph.RemoveEdge(0));
       CHECK_FALSE(undirectedGraph.ContainsEdge(0));
   }

   SUBCASE("Removing a non-existing edge")
   {
       CHECK_FALSE(undirectedGraph.RemoveEdge(20));
   }
}

TEST_CASE("Destroy the graph")
{
    graph::Graph<int32_t, double_t> undirectedGraph;

    undirectedGraph.AddVertex();
    undirectedGraph.AddVertex();
    undirectedGraph.AddVertex();

    REQUIRE(undirectedGraph.GetVertices().Size() >= 3);
    REQUIRE(undirectedGraph.GetNumVertices() >= 3);

    // Add an edge between vertex 0 and 1 with cost 10
    undirectedGraph.AddEdge(0, 1, 10);
    // Add an edge between vertex 1 and 2 with cost 20
    undirectedGraph.AddEdge(1, 2, 20);
    // Add an edge between vertex 2 and 0 with cost 30
    undirectedGraph.AddEdge(2, 0, 30);

    REQUIRE(undirectedGraph.GetEdges().Size() >= 3);

    undirectedGraph.Destroy();

    CHECK(undirectedGraph.GetVertices().Size() == 0);
    CHECK(undirectedGraph.GetEdges().Size() == 0);
    CHECK(undirectedGraph.GetNumVertices() == 0);
    CHECK(undirectedGraph.GetEdges().Size() == 0);
}
