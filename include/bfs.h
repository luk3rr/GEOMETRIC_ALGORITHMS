/*
 * Filename: bfs.h
 * Created on: April  9, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef BFS_H_
#define BFS_H_

#include <cstddef>
#include <limits>

#include "edge.h"
#include "graph.h"
#include "graph_utils.h"
#include "queue_slkd.h"
#include "vertex.h"

namespace graph
{
    /**
     * @brief Perform a Breadth-First Search (BFS) traversal on a graph starting from
     * a given source node
     * @param graph The graph to be traversed
     * @param sourceID The ID of the source node
     *
     * Complexity: O(V + E), when V is the number of vertices and E is the number of
     * edges in the graph
     */
    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    inline void BFS(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                    std::size_t                                 sourceID)
    {
        slkd::Queue<Vertex<typeG, typeT, typeD, nDim>*> queue;

        // Defines the infinity value for the typeG type
        typeG INFINITY_VALUE = std::numeric_limits<typeG>::max();

        // Initialize all vertex costs to infinity and labels to UNVISITED, except
        // source vertex
        for (auto& pair : graph.GetVertices())
        {
            pair.GetSecond().SetCurrentCost(INFINITY_VALUE);
            pair.GetSecond().SetLabel(VertexLabel::UNVISITED);
            pair.GetSecond().SetEdge2Predecessor(nullptr);
        }

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v = nullptr;

        Edge<typeG, typeT, typeD, nDim>* uv;

        u = &graph.GetVertex(sourceID);

        u->SetCurrentCost(0);
        u->SetLabel(VertexLabel::PROCESSING);

        queue.Enqueue(u);

        while (not queue.IsEmpty())
        {
            u = queue.Dequeue();

            // Pair<first, second> = <ID, Edge>
            for (auto& pair : u->GetAdjacencyList())
            {
                uv = pair.GetSecond();

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertex(uv->GetVertices().GetSecond()->GetID())
                    : v = &graph.GetVertex(uv->GetVertices().GetFirst()->GetID());

                if (v->GetLabel() == VertexLabel::UNVISITED)
                {
                    v->SetLabel(VertexLabel::PROCESSING);
                    v->SetCurrentCost(u->GetCurrentCost() + 1);
                    queue.Enqueue(v);
                }
            }

            u->SetLabel(VertexLabel::VISITED);
        }
    }
} // namespace graph

#endif // BFS_H_
