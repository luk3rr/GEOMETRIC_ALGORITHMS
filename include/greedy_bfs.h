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
        bheap::PriorityQueue<
            Vertex<typeG, typeT, typeD, nDim>*,
            decltype(compare::VertexHeuristic<typeG, typeT, typeD, nDim>)>
            minPQueue;

        // Set all vertices as not visited
        for (std::size_t i = 0; i < graph.GetVertices().Size(); i++)
        {
            graph.GetVertices().At(i).SetLabel(VertexLabel::UNVISITED);
            graph.GetVertices().At(i).SetHeuristicCost(0);
            graph.GetVertices().At(i).SetEdge2Predecessor(nullptr);
        }

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* t = nullptr;

        // Check if source and target vertices are valid
        try
        {
            u = &graph.GetVertices().At(sourceID);
            v = nullptr;
            t = &graph.GetVertices().At(targetID);
        }
        catch (const std::out_of_range& e)
        {
            // sourceID or targetID are invalid, that is, they are not in the graph
            return false;
        }

        Edge<typeG, typeT, typeD, nDim>* uv;

        Vector<Edge<typeG, typeT, typeD, nDim>*> uAdjList;

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
                return true;
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
                    v->SetEdge2Predecessor(uv);

                    minPQueue.Enqueue(v);
                }
            }
        }

        return false;
    }

} // namespace graph

#endif // GREEDY_BFS_H_
