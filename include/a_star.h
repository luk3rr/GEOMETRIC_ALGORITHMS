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
        for (std::size_t i = 0; i < graph.GetVertices().Size(); i++)
        {
            graph.GetVertices().At(i).SetLabel(VertexLabel::UNVISITED);
            graph.GetVertices().At(i).SetCurrentCost(INFINITY_VALUE);
            graph.GetVertices().At(i).SetHeuristicCost(0);
            graph.GetVertices().At(i).SetEdge2Predecessor(nullptr);
        }

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, typeD, nDim>* u = &graph.GetVertices().At(sourceID);
        Vertex<typeG, typeT, typeD, nDim>* v = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* t = &graph.GetVertices().At(targetID);

        Edge<typeG, typeT, typeD, nDim>* uv;

        Vector<Edge<typeG, typeT, typeD, nDim>*> uAdjList;

        graph.GetVertices().At(sourceID).SetCurrentCost(
            CalculateHeuristic(heuristic, u, t));
        graph.GetVertices().At(sourceID).SetHeuristicCost(
            CalculateHeuristic(heuristic, u, t));

        minPQueue.Enqueue(&graph.GetVertices().At(sourceID));

        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();

            u->SetLabel(VertexLabel::VISITED);

            if (u->GetID() == targetID)
            {
                // PrintPath(graph, u);
                break;
            }

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
                    v->SetHeuristicCost(CalculateHeuristic(heuristic, v, t));

                    if (Relax(u, v, uAdjList.At(i)))
                    {
                        minPQueue.Enqueue(v);
                    }
                }
            }
        }
    }
} // namespace graph

#endif // A_STAR_H_
