/*
 * Filename: ucs.h
 * Created on: April 11, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef UCS_H_
#define UCS_H_

#include <cstddef>
#include <limits>

#include "edge.h"
#include "graph.h"
#include "graph_utils.h"
#include "priority_queue_bheap.h"

namespace graph
{
    /**
     * @brief Runs the Uniform Cost Search algorithm to find the shortest path between
     * two nodes in a graph
     * @param graph The graph to be searched
     * @param sourceID The ID of the source node
     * @param targetID The ID of the target node
     */
    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    inline void UCS(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                    std::size_t                                 sourceID,
                    std::size_t                                 targetID)
    {
        bheap::PriorityQueue<Vertex<typeG, typeT, typeD, nDim>*,
                             decltype(compare::Vertex<typeG, typeT, typeD, nDim>)>
            minPQueue;

        // Defines the infinity value for the typeG type
        typeG INFINITY_VALUE = std::numeric_limits<typeG>::max();

        // Set all vertices as not visited
        // Pair<first, second> = <ID, Vertex>
        for (auto& pair : graph.GetVertices())
        {
            pair.GetSecond().SetLabel(VertexLabel::UNVISITED);
            pair.GetSecond().SetCurrentCost(INFINITY_VALUE);
            pair.GetSecond().SetEdge2Predecessor(nullptr);
        }

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v = nullptr;

        Edge<typeG, typeT, typeD, nDim>* uv;

        u = &graph.GetVertex(sourceID);

        u->SetCurrentCost(0);

        minPQueue.Enqueue(u);

        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();

            u->SetLabel(VertexLabel::VISITED);

            if (u->GetID() == targetID)
                break;

            // Pair<first, second> = <ID, Edge>
            for (auto& pair : u->GetAdjacencyList())
            {
                uv = pair.GetSecond();

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertex(uv->GetVertices().GetSecond()->GetID())
                    : v = &graph.GetVertex(uv->GetVertices().GetFirst()->GetID());

                if (v->GetLabel() == VertexLabel::UNVISITED and Relax(u, v, uv))
                {
                    minPQueue.Enqueue(v);
                }
            }
        }
    }
} // namespace graph

#endif // UCS_H_
