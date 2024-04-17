/*
 * Filename: dfs.h
 * Created on: April  9, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef DFS_H_
#define DFS_H_

#include <cstddef>
#include <cstdint>

#include "graph.h"
#include "graph_utils.h"

namespace graph
{
    namespace
    {
        /**
         * @brief Recursive function that performs the Depth-First Search (DFS)
         * traversal
         * @param graph The graph to be traversed
         * @param sourceID The ID of the source node
         * @param timestamp The time of entering sourceID vertex
         */
        template<typename typeG,
                 typename typeT,
                 typename typeD,
                 std::size_t nDim,
                 bool        directed>
        inline void DFS(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                        std::size_t                                 currentVertexID,
                        uint32_t&                                   timestamp)
        {
            // Auxiliar variables to make code most legible
            Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
            Vertex<typeG, typeT, typeD, nDim>* v = nullptr;

            Edge<typeG, typeT, typeD, nDim>* uv;

            u = &graph.GetVertex(currentVertexID);

            u->SetArrivalTime(++timestamp);
            u->SetLabel(VertexLabel::VISITED);


            for (auto& pair : u->GetAdjacencyList())
            {
                // Edge uv (or vu, if is non-directed)
                uv = pair.GetSecond();

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertex(uv->GetVertices().GetSecond()->GetID())
                    : v = &graph.GetVertex(uv->GetVertices().GetFirst()->GetID());

                if (v->GetLabel() == VertexLabel::UNVISITED)
                {
                    DFS(graph, v->GetID(), timestamp);
                }
            }

            u->SetDepartureTime(++timestamp);
        }
    } // namespace

    /**
     * @brief Perform a Depth-First Search (DFS) traversal on a graph starting from
     * a given source node
     * @param graph The graph to be traversed
     * @param sourceID The ID of the source node
     *
     * Complexity: O(V + E), when V is the number of vertices and E is the number of
     * edges in the graph
     */
    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    inline void DFS(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                    std::size_t                                 sourceID)
    {
        for (auto& pair : graph.GetVertices())
        {
            pair.GetSecond().SetLabel(VertexLabel::UNVISITED);
        }

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v = nullptr;

        Edge<typeG, typeT, typeD, nDim>* uv = nullptr;

        uint32_t timestamp = 0;

        u = &graph.GetVertex(sourceID);

        u->SetArrivalTime(timestamp);
        u->SetLabel(VertexLabel::VISITED);

        for (auto& pair : u->GetAdjacencyList())
        {
            // Edge uv (or vu, if is non-directed)
            uv = pair.GetSecond();

            // Get the pointer do neighbor vertex, since one end of the edge is
            // vertex u, and the other end is vertex v
            uv->GetVertices().GetFirst()->GetID() == u->GetID()
                ? v = &graph.GetVertex(uv->GetVertices().GetSecond()->GetID())
                : v = &graph.GetVertex(uv->GetVertices().GetFirst()->GetID());

            if (v->GetLabel() == VertexLabel::UNVISITED)
            {
                DFS(graph, v->GetID(), timestamp);
            }
        }

        u->SetDepartureTime(++timestamp);
    }

} // namespace graph
#endif // DFS_H_
