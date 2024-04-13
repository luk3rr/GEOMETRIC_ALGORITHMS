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
        for (std::size_t i = 0; i < graph.GetVertices().Size(); i++)
        {
            if (i != sourceID)
                graph.GetVertices().At(i).SetCurrentCost(INFINITY_VALUE);

            graph.GetVertices().At(i).SetLabel(VertexLabel::UNVISITED);
            graph.GetVertices().At(i).SetEdge2Predecessor(nullptr);
        }

        graph.GetVertices().At(sourceID).SetCurrentCost(0);
        graph.GetVertices().At(sourceID).SetLabel(VertexLabel::PROCESSING);

        queue.Enqueue(&graph.GetVertices().At(sourceID));

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v = nullptr;

        Edge<typeG, typeT, typeD, nDim>* uv;

        Vector<Edge<typeG, typeT, typeD, nDim>*> uAdjList;

        while (not queue.IsEmpty())
        {
            u = queue.Dequeue();

            uAdjList = u->GetAdjacencyList();

            for (std::size_t i = 0; i < uAdjList.Size(); i++)
            {
                uv = uAdjList.At(i);

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertices()[uv->GetVertices().GetSecond()->GetID()]
                    : v = &graph.GetVertices()[uv->GetVertices().GetFirst()->GetID()];

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
