/*
 * Filename: a_star.h
 * Created on: April 11, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef A_STAR_H_
#define A_STAR_H_

#include <cstddef>
#include <limits>

#include "edge.h"
#include "graph.h"
#include "graph_utils.h"
#include "heuristics.h"
#include "priority_queue_bheap.h"

namespace graph
{
    /**
     * @brief A* algorithm to find the shortest path between two nodes in a graph
     * @param graph The graph to search
     * @param sourceID The ID of the source node
     * @param targetID The ID of the target node
     * @param heuristic The heuristic function to estimate the cost to reach the
     * target node
     */
    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    inline void AStar(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                      std::size_t                                 sourceID,
                      std::size_t                                 targetID,
                      heuristics::distance::Heuristic             heuristic =
                          heuristics::distance::Heuristic::EUCLIDEAN)
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
            pair.GetSecond().SetHeuristicCost(INFINITY_VALUE);
        }

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* t = nullptr;

        Edge<typeG, typeT, typeD, nDim>* uv;

        u = &graph.GetVertex(sourceID);
        t = &graph.GetVertex(targetID);

        u->SetCurrentCost(CalculateHeuristic(heuristic, u, t));
        u->SetHeuristicCost(CalculateHeuristic(heuristic, u, t));

        minPQueue.Enqueue(u);

        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();

            u->SetLabel(VertexLabel::VISITED);

            if (u->GetID() == targetID)
            {
                // PrintPath(graph, u);
                break;
            }

            // Pair<first, second> = <ID, Edge>
            for (auto& pair : u->GetAdjacencyList())
            {
                // Edge uv (or vu, if is non-directed)
                uv = pair.GetSecond();

                v = GetAdjacentVertex(graph, u, uv);

                if (v->GetLabel() == VertexLabel::UNVISITED)
                {
                    v->SetHeuristicCost(CalculateHeuristic(heuristic, v, t));

                    if (Relax(u, v, uv))
                    {
                        minPQueue.Enqueue(v);
                    }
                }
            }
        }
    }
} // namespace graph

#endif // A_STAR_H_
