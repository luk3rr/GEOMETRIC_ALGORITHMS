/*
 * Filename: bfs_test.cc
 * Created on: April  9, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include "bfs.h"

TEST_CASE("BFS algorithm test")
{
    // Create a graph with some vertices and edges
    graph::Graph<uint32_t, uint32_t> graph(9, 14);

    graph.AddVertex(graph::Vertex<uint32_t, uint32_t>(0));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t>(1));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t>(2));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t>(3));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t>(4));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t>(5));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t>(6));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t>(7));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t>(8));

    // {vertex_i_ID, vertex_j_ID, cost of the edge connecting the two}
    // This graph can be found in the book 'Introduction to Algorithms,' by Thomas
    // Cormen, third edition, Figure 23.5
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 7);
    graph.AddEdge(1, 7);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 3);
    graph.AddEdge(2, 8);
    graph.AddEdge(2, 5);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 5);
    graph.AddEdge(4, 5);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 7);
    graph.AddEdge(6, 8);
    graph.AddEdge(7, 8);

    graph::BFS(graph, 0);

    // Check if the shortest paths have been computed correctly
    CHECK(graph.GetVertices().At(0).GetCurrentCost() == 0);
    CHECK(graph.GetVertices().At(1).GetCurrentCost() == 1);
    CHECK(graph.GetVertices().At(2).GetCurrentCost() == 2);
    CHECK(graph.GetVertices().At(3).GetCurrentCost() == 3);
    CHECK(graph.GetVertices().At(4).GetCurrentCost() == 4);
    CHECK(graph.GetVertices().At(5).GetCurrentCost() == 3);
    CHECK(graph.GetVertices().At(6).GetCurrentCost() == 2);
    CHECK(graph.GetVertices().At(7).GetCurrentCost() == 1);
    CHECK(graph.GetVertices().At(8).GetCurrentCost() == 2);
}
