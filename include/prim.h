/*
 * Filename: prim.h
 * Created on: April  9, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef PRIM_H_
#define PRIM_H_

#include <cstddef>
#include <limits>

#include "edge.h"
#include "graph.h"
#include "graph_utils.h"
#include "priority_queue_bheap.h"
#include "vector.h"

namespace graph
{

    /**
     * @brief Run Prim's algorithm to find Minimum Spanning Tree starting from a
     *        given source vertex
     * @param graph The graph on which to calculate the MST
     * @param sourceID The source vertex id from which to begin the MST
     *        calculation
     **/
    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    inline void Prim(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                     std::size_t                                 sourceID)
    {
        bheap::PriorityQueue<Vertex<typeG, typeT, typeD, nDim>*,
                             decltype(compare::Vertex<typeG, typeT, typeD, nDim>)>
            minPQueue;

        // Defines the infinity value for the typeG type
        typeG INFINITY_VALUE = std::numeric_limits<typeG>::max();

        // Initialize all vertex costs to infinity
        // Pair<first, second> = <ID, Vertex>
        for (auto& pair : graph.GetVertices())
        {
            pair.GetSecond().SetCurrentCost(INFINITY_VALUE);
            pair.GetSecond().SetEdge2Predecessor(nullptr);
        }

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, typeD, nDim>* u  = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v  = nullptr;
        Edge<typeG, typeT, typeD, nDim>*   uv = nullptr;

        // A vector to track whether a vertex with ID as the index has been visited or
        // not
        Vector<bool> inMst(graph.GetVertices().Size(), false);

        minPQueue.Enqueue(&graph.GetVertex(sourceID));

        Vector<Vertex<typeG, typeT, typeD, nDim>*> aux;

        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();

            // Pair<first, second> = <ID, Edge>
            for (auto& pair : u->GetAdjacencyList())
            {
                // Edge uv (or vu, if is non-directed)
                uv = pair.GetSecond();

                v = GetAdjacentVertex(graph, u, uv);

                // Check if the neighbor vertex 'v' is not in the Minimum Spanning Tree
                // (MST) and if the cost of the edge 'uv' is less than the current cost
                // of 'v'
                if (not inMst[v->GetID()] and uv->GetCost() < v->GetCurrentCost())
                {
                    // Update the cost of 'v' and enqueue it to reposition it in the
                    // queue based on the new cost
                    v->SetEdge2Predecessor(uv);
                    v->SetCurrentCost(uv->GetCost());
                    minPQueue.Enqueue(v);
                }
            }

            // Set 'u' as checked
            inMst[u->GetID()] = true;
        }
    }
} // namespace graph

#endif // PRIM_H_
