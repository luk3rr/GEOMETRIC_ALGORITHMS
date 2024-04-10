/*
 * Filename: main.cc
 * Created on: October  8, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cstdlib>

#include "dfs.h"

int main() { 
    
    // Create a graph with some vertices and edges
    graph::Graph<uint32_t, uint32_t, 2, false> graph(9, 14);

    graph.AddVertex(graph::Vertex<uint32_t, uint32_t, 2>(0));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t, 2>(1));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t, 2>(2));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t, 2>(3));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t, 2>(4));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t, 2>(5));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t, 2>(6));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t, 2>(7));
    graph.AddVertex(graph::Vertex<uint32_t, uint32_t, 2>(8));

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

    return EXIT_SUCCESS;
}
