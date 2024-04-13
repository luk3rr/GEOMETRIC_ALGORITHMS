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
    graph::Graph<int32_t, double_t, 2, false> undirectedGraph(3, 3);

    SUBCASE("Add vertices to the graph")
    {
        graph::Vertex<int32_t, double_t, 2> vertex1(0);
        graph::Vertex<int32_t, double_t, 2> vertex2(1);
        graph::Vertex<int32_t, double_t, 2> vertex3(2);

        undirectedGraph.AddVertex(vertex1);
        undirectedGraph.AddVertex(vertex2);
        undirectedGraph.AddVertex(vertex3);

        CHECK(undirectedGraph.GetVertices().Size() == 3);
        CHECK(undirectedGraph.GetNumVertices() == 3);
    }

    SUBCASE("Add edges to the graph")
    {
        graph::Vertex<int32_t, double_t, 2> vertex1(0);
        graph::Vertex<int32_t, double_t, 2> vertex2(1);
        graph::Vertex<int32_t, double_t, 2> vertex3(2);

        undirectedGraph.AddVertex(vertex1);
        undirectedGraph.AddVertex(vertex2);
        undirectedGraph.AddVertex(vertex3);

        // Add an edge between vertex 0 and 1 with cost 10
        undirectedGraph.AddEdge(0, 1, 10);
        // Add an edge between vertex 1 and 2 with cost 20
        undirectedGraph.AddEdge(1, 2, 20);
        // Add an edge between vertex 2 and 0 with cost 30
        undirectedGraph.AddEdge(2, 0, 30);

        CHECK(undirectedGraph.GetEdges().Size() == 3);
    }
}

TEST_CASE("AddVertexWithIncrementalID")
{
    graph::Graph<int32_t, double_t, 2, false> undirectedGraph(3, 3);

    SUBCASE("Add vertices to the graph")
    {
        graph::Vertex<int32_t, double_t, 2> vertex1(0);
        graph::Vertex<int32_t, double_t, 2> vertex2(1);
        graph::Vertex<int32_t, double_t, 2> vertex3(2);
        graph::Vertex<int32_t, double_t, 2> vertex4(
            3); // ID greater than the number of vertices

        undirectedGraph.AddVertex(vertex1);
        undirectedGraph.AddVertex(vertex2);
        undirectedGraph.AddVertex(vertex3);
        undirectedGraph.AddVertex(vertex4);

        CHECK(undirectedGraph.GetVertices().Size() == 4);
        CHECK(undirectedGraph.GetNumVertices() == 4);
    }
}
