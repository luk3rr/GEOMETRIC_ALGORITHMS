/*
 * Filename: ucs.h
 * Created on: April 11, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef UCS_H_
#define UCS_H_

#include <cstddef>
#include <cstdint>
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
    template<typename typeG, typename typeT, std::size_t nDim>
    inline void
    UCS(Graph<typeG, typeT, nDim>& graph, std::size_t sourceID, std::size_t targetID)
    {
        bheap::PriorityQueue<Vertex<typeG, typeT, nDim>*,
                             decltype(compare::Vertex<typeG, typeT, nDim>)>
            minPQueue;

        // Defines the infinity value for the typeG type
        typeG INFINITY_VALUE = std::numeric_limits<typeG>::max();

        // Set all vertices as not visited
        for (std::size_t i = 0; i < graph.GetVertices().Size(); i++)
        {
            graph.GetVertices().At(i).SetLabel(VertexLabel::UNVISITED);
            graph.GetVertices().At(i).SetCurrentCost(INFINITY_VALUE);
            graph.GetVertices().At(i).SetEdge2Predecessor(nullptr);
        }

        graph.GetVertices().At(sourceID).SetCurrentCost(0);

        minPQueue.Enqueue(&graph.GetVertices().At(sourceID));

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, nDim>* u = nullptr;
        Vertex<typeG, typeT, nDim>* v = nullptr;

        Edge<typeG, typeT, nDim>* uv;

        Vector<Edge<typeG, typeT, nDim>*> uAdjList;

        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();

            u->SetLabel(VertexLabel::VISITED);

            if (u->GetID() == targetID)
                break;

            uAdjList = u->GetAdjacencyList();

            for (std::size_t i = 0; i < uAdjList.Size(); i++)
            {
                uv = uAdjList.At(i);

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertices()[uv->GetVertices().GetSecond()->GetID()]
                    : v = &graph.GetVertices()[uv->GetVertices().GetFirst()->GetID()];

                if (v->GetLabel() == VertexLabel::UNVISITED and Relax(u, v, uAdjList.At(i)))
                {
                    minPQueue.Enqueue(v);
                }
            }
        }
    }
} // namespace graph

#endif // UCS_H_
