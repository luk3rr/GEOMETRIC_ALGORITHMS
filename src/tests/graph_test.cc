/*
 * Filename: graph_test.cc
 * Created on: November  2, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"
#include "graph.h"

TEST_CASE("CreateGraph")
{
    SUBCASE("Create an undirected graph with 3 vertices and 3 edges")
    {
        graph::Graph<double_t, double_t, 2, false> undirectedGraph(3, 3);

        CHECK(undirectedGraph.GetVertices().Size() == 3);
        CHECK(undirectedGraph.GetEdges().Size() == 3);
    }

    SUBCASE("Create a directed graph with 4 vertices and 6 edges")
    {
        graph::Graph<int32_t, double_t, 2, true> directedGraph(4, 6);

        CHECK(directedGraph.GetVertices().Size() == 4);
        CHECK(directedGraph.GetEdges().Size() == 6);
    }
}

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
