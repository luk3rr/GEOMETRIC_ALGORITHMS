/*
 * Filename: ucs_test.cc
 * Created on: April 11, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <cstdint>

#include "ucs.h"

TEST_CASE("Uniform-Cost Search algorithm test")
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

    // {vertex_i_ID, vertex_j_ID, cost of the edge connecting the two}
    // This graph can be found in the book 'Introduction to Algorithms,' by Thomas
    // Cormen, third edition, Figure 23.5
    graph.AddEdge(0, 1, 4);
    graph.AddEdge(0, 7, 8);
    graph.AddEdge(1, 7, 11);
    graph.AddEdge(1, 2, 8);
    graph.AddEdge(2, 3, 7);
    graph.AddEdge(2, 8, 2);
    graph.AddEdge(2, 5, 4);
    graph.AddEdge(3, 4, 9);
    graph.AddEdge(3, 5, 14);
    graph.AddEdge(4, 5, 10);
    graph.AddEdge(5, 6, 2);
    graph.AddEdge(6, 7, 1);
    graph.AddEdge(6, 8, 6);
    graph.AddEdge(7, 8, 7);

    graph::UCS(graph, 0, 8);

    CHECK(graph.GetVertices().At(8).GetCurrentCost() == 14);
}
