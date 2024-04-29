/*
 * Filename: ida_star.h
 * Created on: April 27, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef IDA_STAR_H_
#define IDA_STAR_H_

#include "graph.h"
#include "graph_utils.h"
#include "heuristics.h"
#include "priority_queue_bheap.h"
#include "vertex.h"

namespace graph
{
    namespace
    {
        /**
         * @brief Recursive function that performs the Iterative Deepening A* search
         *
         * @param graph The graph to be traversed
         * @param currentVertexID The current vertex being visited
         * @param targetVertexID The target vertex to be reached
         * @param depth The current depth of the search
         * @param label The current label of the search
         * @return True if the target vertex is reached, false otherwise
         **/
        template<typename typeG,
                 typename typeT,
                 typename typeD,
                 std::size_t nDim,
                 bool        directed>
        inline bool IDAStar(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                            std::size_t                                 currentVertexID,
                            std::size_t                                 targetVertexID,
                            std::size_t                                 depth,
                            std::size_t                                 label,
                            heuristics::distance::Heuristic             heuristic =
                                heuristics::distance::Heuristic::EUCLIDEAN)
        {
            if (currentVertexID == targetVertexID)
                return true;

            if (depth <= 0)
                return false;

            // Auxiliar variables to make code most legible
            Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
            Vertex<typeG, typeT, typeD, nDim>* v = nullptr;

            Edge<typeG, typeT, typeD, nDim>* uv;

            u = &graph.GetVertex(currentVertexID);

            u->SetLabel(label);

            // Use priority queue to get the child with the smallest cost
            bheap::PriorityQueue<Vertex<typeG, typeT, typeD, nDim>*,
                                 decltype(compare::Vertex<typeG, typeT, typeD, nDim>)>
                minPQueue;

            // Add all neighbors of vertex u to the priority queue
            // Pair<first, second> = <ID, Edge>
            for (auto& pair : u->GetAdjacencyList())
            {
                uv = pair.GetSecond();

                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertex(uv->GetVertices().GetSecond()->GetID())
                    : v = &graph.GetVertex(uv->GetVertices().GetFirst()->GetID());

                if (v->GetLabel() != label)
                {
                    v->SetHeuristicCost(
                        CalculateHeuristic(heuristic,
                                           v,
                                           &graph.GetVertex(targetVertexID)));

                    if (Relax(u, v, uv))
                    {
                        v->SetLabel(label);
                        minPQueue.Push(v);
                    }
                }
            }

            while (not minPQueue.IsEmpty())
            {
                v = minPQueue.Dequeue();

                if (IDAStar(graph, v->GetID(), targetVertexID, --depth, label))
                    return true;
            }

            return false;
        }
    } // namespace

    /**
     * @brief Iterative Deepening A* search algorithm
     *
     * @param graph The graph to be traversed
     * @param startVertexID The start vertex
     * @param targetVertexID The target vertex
     * @param maxDepth The maximum depth of the search
     * @param heuristic The heuristic to be used
     * @return True if the target vertex is reached, false otherwise
     **/
    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    inline bool IDAStar(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                        std::size_t                                 startVertexID,
                        std::size_t                                 targetVertexID,
                        std::size_t                                 maxDepth,
                        heuristics::distance::Heuristic             heuristic =
                            heuristics::distance::Heuristic::EUCLIDEAN)
    {
        typeG INFINITY_VALUE = std::numeric_limits<typeG>::max();

        // Set the current cost of all vertices to infinity
        for (auto& pair : graph.GetVertices())
            pair.GetSecond().SetCurrentCost(INFINITY_VALUE);

        graph.GetVertex(startVertexID).SetCurrentCost(0);

        for (std::size_t i = 0; i < maxDepth; i++)
        {
            if (IDAStar(graph, startVertexID, targetVertexID, i, i, heuristic))
                return true;

            // Reset the costs of the vertices
            for (auto& pair : graph.GetVertices())
                pair.GetSecond().SetCurrentCost(INFINITY_VALUE);

            // Set the cost of the start vertex to 0
            graph.GetVertex(startVertexID).SetCurrentCost(0);
        }

        return false;
    }
} // namespace graph

#endif // IDA_STAR_H_
