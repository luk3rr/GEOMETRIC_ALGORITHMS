/*
 * Filename: dijkstra.h
 * Created on: April  9, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <limits>

#include "edge.h"
#include "graph.h"
#include "graph_utils.h"
#include "priority_queue_bheap.h"
#include "vertex.h"

namespace graph
{
    /**
     * @brief Run Dijkstra's algorithm to find the shortest paths from a given
     *        source vertex
     * @param graph The graph on which to calculate the shortest paths
     * @param sourceID The source vertex id from which to calculate the shortest
     *        paths
     **/
    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    inline void Dijkstra(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                         std::size_t                                 sourceID)

    {
        bheap::PriorityQueue<Vertex<typeG, typeT, typeD, nDim>*,
                             decltype(compare::Vertex<typeG, typeT, typeD, nDim>)>
            minPQueue;

        // Defines the infinity value for the typeG type
        typeG INFINITY_VALUE = std::numeric_limits<typeG>::max();

        // Initialize all vertex costs to infinity
        for (auto& pair : graph.GetVertices())
        {
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

            // Pair<first, second> = <ID, Edge>
            for (auto& pair : u->GetAdjacencyList())
            {
                // Edge uv (or vu, if is non-directed)
                uv = pair.GetSecond();

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertex(uv->GetVertices().GetSecond()->GetID())
                    : v = &graph.GetVertex(uv->GetVertices().GetFirst()->GetID());

                if (Relax(u, v, uv))
                {
                    // If the neighbor's cost is updated, then add again to queue to
                    // update all neighbors with new cost
                    minPQueue.Enqueue(v);
                }
            }
        }
    }

} // namespace graph

#endif // DIJKSTRA_H_
