/*
 * Filename: dfs.h
 * Created on: April  9, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef DFS_H_
#define DFS_H_

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
        template<typename typeG, typename typeT, std::size_t nDim>
        inline void DFS(Graph<typeG, typeT, nDim>& graph,
                        std::size_t                currentVertexID,
                        uint32_t&                  timestamp)
        {

            graph.GetVertices().At(currentVertexID).SetArrivalTime(++timestamp);
            graph.GetVertices().At(currentVertexID).SetLabel(VertexLabel::VISITED);

            // Auxiliar variables to make code most legible
            Vertex<typeG, typeT, nDim>* u = nullptr;
            Vertex<typeG, typeT, nDim>* v = nullptr;

            Edge<typeG, typeT, nDim>* uv;

            Vector<Edge<typeG, typeT, nDim>*> uAdjList =
                graph.GetVertices().At(currentVertexID).GetAdjacencyList();

            u = &graph.GetVertices().At(currentVertexID);

            for (std::size_t i = 0; i < uAdjList.Size(); i++)
            {
                // Edge uv (or vu, if is non-directed)
                uv = uAdjList.At(i);

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertices()[uv->GetVertices().GetSecond()->GetID()]
                    : v = &graph.GetVertices()[uv->GetVertices().GetFirst()->GetID()];

                if (v->GetLabel() == VertexLabel::UNVISITED)
                {
                    DFS(graph, v->GetID(), timestamp);
                }
            }

            graph.GetVertices().At(currentVertexID).SetDepartureTime(++timestamp);
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
    template<typename typeG, typename typeT, std::size_t nDim>
    inline void DFS(Graph<typeG, typeT, nDim>& graph, std::size_t sourceID)
    {
        for (std::size_t i = 0; i < graph.GetVertices().Size(); i++)
        {
            graph.GetVertices().At(i).SetLabel(VertexLabel::UNVISITED);
        }

        uint32_t timestamp = 0;

        graph.GetVertices().At(sourceID).SetArrivalTime(timestamp);
        graph.GetVertices().At(sourceID).SetLabel(VertexLabel::VISITED);

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, nDim>* u = nullptr;
        Vertex<typeG, typeT, nDim>* v = nullptr;

        Edge<typeG, typeT, nDim>* uv = nullptr;

        Vector<Edge<typeG, typeT, nDim>*> uAdjList =
            graph.GetVertices().At(sourceID).GetAdjacencyList();

        u = &graph.GetVertices().At(sourceID);

        for (std::size_t i = 0; i < uAdjList.Size(); i++)
        {
            // Edge uv (or vu, if is non-directed)
            uv = uAdjList.At(i);

            // Get the pointer do neighbor vertex, since one end of the edge is
            // vertex u, and the other end is vertex v
            uv->GetVertices().GetFirst()->GetID() == u->GetID()
                ? v = &graph.GetVertices()[uv->GetVertices().GetSecond()->GetID()]
                : v = &graph.GetVertices()[uv->GetVertices().GetFirst()->GetID()];

            if (v->GetLabel() == VertexLabel::UNVISITED)
            {
                DFS(graph, v->GetID(), timestamp);
            }
        }

        graph.GetVertices().At(sourceID).SetDepartureTime(++timestamp);
    }

} // namespace graph
#endif // DFS_H_
