/*
 * Filename: iddfs_test.cc
 * Created on: April 10, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include "iddfs.h"

TEST_CASE("IDDFS algorithm test")
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

    CHECK(graph::IDDFS(graph, 0, 4, 100));
    CHECK(graph::IDDFS(graph, 0, 8, 100));
    CHECK(graph::IDDFS(graph, 4, 3, 100));
    CHECK(graph::IDDFS(graph, 4, 3, 100));
    CHECK_FALSE(graph::IDDFS(graph, 0, 100, 200));
}
