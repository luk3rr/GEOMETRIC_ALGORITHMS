/*
 * Filename: graph_test.cc
 * Created on: November  2, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <random>

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

TEST_CASE("Insert random number of vertices and edges")
{
    graph::Graph<int32_t, double_t> undirectedGraph;

    // Create K50 graph
    const int32_t numVertices = 50;
    const int32_t numEdges    = numVertices * (numVertices - 1) / 2;

    for (int32_t i = 0; i < numVertices; i++)
    {
        undirectedGraph.AddVertex();
    }

    REQUIRE(undirectedGraph.GetNumVertices() == numVertices);

    for (int32_t i = 0; i < numVertices; i++)
    {
        for (int32_t j = i + 1; j < numVertices; j++)
        {
            undirectedGraph.AddEdge(i, j);
        }
    }

    REQUIRE(undirectedGraph.GetEdges().Size() == numEdges);

    // Use the current time as seed for the random number generator
    auto now    = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value  = now_ms.time_since_epoch();
    auto seed   = value.count();

    std::mt19937                    gen(seed);
    std::uniform_int_distribution<> dis(0, numVertices - 1);

    uint32_t numVerticesRemoved   = 0;
    uint32_t numEdgesRemoved      = 0;
    uint32_t vertexToRemove       = 0;
    uint32_t vertexToRemoveDegree = 0;

    for (std::size_t i = 0; i < numVertices; i++)
    {
        // Randomly select a vertex to remove
        vertexToRemove = dis(gen);

        if (undirectedGraph.ContainsVertex(vertexToRemove))
        {
            vertexToRemoveDegree =
                undirectedGraph.GetVertex(vertexToRemove).GetDegree();

            if (undirectedGraph.RemoveVertex(vertexToRemove))
            {
                numVerticesRemoved++;
                numEdgesRemoved += vertexToRemoveDegree;
            }
        }
    }

    CHECK(undirectedGraph.GetNumVertices() == numVertices - numVerticesRemoved);
    CHECK(undirectedGraph.GetNumEdges() == numEdges - numEdgesRemoved);
}
