/*
 * Filename: greedy_bfs.h
 * Created on: April 12, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef GREEDY_BFS_H_
#define GREEDY_BFS_H_

#include <cstddef>
#include <stdexcept>

#include "graph.h"
#include "graph_utils.h"
#include "heuristics.h"
#include "priority_queue_bheap.h"

namespace graph
{
    /**
     * @brief Greedy Best-First Search algorithm to find the shortest path between
     * two vertices in a graph
     * @param graph Graph to be searched
     * @param sourceID ID of the source vertex
     * @param targetID ID of the target vertex
     * @param heuristic Heuristic to be used in the algorithm
     */
    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    inline bool GreedyBFS(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                          std::size_t                                 sourceID,
                          std::size_t                                 targetID,
                          heuristics::distance::Heuristic             heuristic =
                              heuristics::distance::Heuristic::EUCLIDEAN)
    {
        // Check if the graph contains the source and target vertices
        if (not(graph.ContainsVertex(sourceID) and graph.ContainsVertex(targetID)))
            return false;

        bheap::PriorityQueue<
            Vertex<typeG, typeT, typeD, nDim>*,
            decltype(compare::VertexHeuristic<typeG, typeT, typeD, nDim>)>
            minPQueue;

        // Set all vertices as not visited
        // Pair<first, second> = <ID, Vertex>
        for (auto& pair : graph.GetVertices())
        {
            pair.GetSecond().SetLabel(VertexLabel::UNVISITED);
            pair.GetSecond().SetHeuristicCost(0);
            pair.GetSecond().SetEdge2Predecessor(nullptr);
        }

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* t = nullptr;

        Edge<typeG, typeT, typeD, nDim>* uv;

        try
        {
            u = &graph.GetVertex(sourceID);
            t = &graph.GetVertex(targetID);
        }
        catch (const std::out_of_range& e)
        {
            return false;
        }

        u->SetHeuristicCost(CalculateHeuristic(heuristic, u, t));

        minPQueue.Enqueue(u);

        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();

            u->SetLabel(VertexLabel::VISITED);

            if (u->GetID() == targetID)
            {
                // PrintPath(graph, u);
                return true;
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
                    v->SetEdge2Predecessor(uv);

                    minPQueue.Enqueue(v);
                }
            }
        }

        return false;
    }

} // namespace graph

#endif // GREEDY_BFS_H_
