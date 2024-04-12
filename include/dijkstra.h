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
#include "vector.h"
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
    template<typename typeG, typename typeT, std::size_t nDim>
    inline void Dijkstra(Graph<typeG, typeT, nDim>& graph, std::size_t sourceID)

    {
        bheap::PriorityQueue<Vertex<typeG, typeT, nDim>*,
                             decltype(compare::Vertex<typeG, typeT, nDim>)>
            minPQueue;

        // Defines the infinity value for the typeG type
        typeG INFINITY_VALUE = std::numeric_limits<typeG>::max();

        // Initialize all vertex costs to infinity
        for (std::size_t i = 0; i < graph.GetVertices().Size(); i++)
        {
            if (i != sourceID)
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

            uAdjList = u->GetAdjacencyList();

            for (std::size_t i = 0; i < uAdjList.Size(); i++)
            {
                // Edge uv (or vu, if is non-directed)
                uv = uAdjList.At(i);

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertices()[uv->GetVertices().GetSecond()->GetID()]
                    : v = &graph.GetVertices()[uv->GetVertices().GetFirst()->GetID()];

                if (Relax(u, v, uAdjList.At(i)))
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
