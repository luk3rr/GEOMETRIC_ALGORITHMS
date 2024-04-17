/*
 * Filename: dfs_test.cc
 * Created on: April  9, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include "dfs.h"

TEST_CASE("DFS algorithm test")
{
    // Create a graph with some vertices and edges
    graph::Graph<uint32_t, uint32_t> graph;

    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    // {vertex_i_ID, vertex_j_ID}
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

    graph::DFS(graph, 0);

    // Check if the vertices have been visited correctly
    CHECK(graph.GetVertices().At(0).GetArrivalTime() == 0);
    CHECK(graph.GetVertices().At(1).GetArrivalTime() == 1);
    CHECK(graph.GetVertices().At(2).GetArrivalTime() == 5);
    CHECK(graph.GetVertices().At(3).GetArrivalTime() == 6);
    CHECK(graph.GetVertices().At(4).GetArrivalTime() == 7);
    CHECK(graph.GetVertices().At(5).GetArrivalTime() == 4);
    CHECK(graph.GetVertices().At(6).GetArrivalTime() == 3);
    CHECK(graph.GetVertices().At(7).GetArrivalTime() == 2);
    CHECK(graph.GetVertices().At(8).GetArrivalTime() == 10);

    CHECK(graph.GetVertices().At(8).GetDepartureTime() == 11);
    CHECK(graph.GetVertices().At(7).GetDepartureTime() == 15);
    CHECK(graph.GetVertices().At(6).GetDepartureTime() == 14);
    CHECK(graph.GetVertices().At(5).GetDepartureTime() == 13);
    CHECK(graph.GetVertices().At(4).GetDepartureTime() == 8);
    CHECK(graph.GetVertices().At(3).GetDepartureTime() == 9);
    CHECK(graph.GetVertices().At(2).GetDepartureTime() == 12);
    CHECK(graph.GetVertices().At(1).GetDepartureTime() == 16);
    CHECK(graph.GetVertices().At(0).GetDepartureTime() == 17);
}
