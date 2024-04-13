/*
 * Filename: iddfs.h
 * Created on: April 10, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef IDDFS_H_
#define IDDFS_H_

#include <cstddef>

#include "graph.h"

namespace graph
{
    namespace
    {
        /**
         * @brief Recursive function that performs the Iterative Deepening Depth First
         * Search
         * @param graph The graph to be traversed
         * @param currentVertexID The current vertex being visited
         * @param targetVertexID The target vertex to be reached
         * @param depth The current depth of the search
         * @param label The current label of the search
         * @return True if the target vertex is reached, false otherwise
         */
        template<typename typeG,
                 typename typeT,
                 typename typeD,
                 std::size_t nDim,
                 bool        directed>
        inline bool IDDFS(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                          std::size_t                                 currentVertexID,
                          std::size_t                                 targetVertexID,
                          std::size_t                                 depth,
                          std::size_t                                 label)
        {
            if (currentVertexID == targetVertexID)
                return true;

            if (depth <= 0)
                return false;

            graph.GetVertices().At(currentVertexID).SetLabel(label);

            // Auxiliar variables to make code most legible
            Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
            Vertex<typeG, typeT, typeD, nDim>* v = nullptr;

            Edge<typeG, typeT, typeD, nDim>* uv;

            Vector<Edge<typeG, typeT, typeD, nDim>*> uAdjList =
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

                if (v->GetLabel() != label)
                {
                    if (IDDFS(graph, v->GetID(), targetVertexID, --depth, label))
                        return true;
                }
            }

            return false;
        }
    } // namespace

    /**
     * @brief Iterative Deepening Depth First Search
     * @param graph The graph to be traversed
     * @param startVertexID The start vertex
     * @param targetVertexID The target vertex
     * @param maxDepth The maximum depth of the search
     * @return True if the target vertex is reached, false otherwise
     *
     * Complexity: O(b^d), where b is the branching factor and d is the depth of the
     * shallowest solution
     */
    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    inline bool IDDFS(Graph<typeG, typeT, typeD, nDim, directed>& graph,
                      std::size_t                                 startVertexID,
                      std::size_t                                 targetVertexID,
                      std::size_t                                 maxDepth)
    {
        for (std::size_t i = 0; i < maxDepth; i++)
        {
            if (IDDFS(graph, startVertexID, targetVertexID, i, i))
            {
                return true;
            }
        }

        return false;
    }
} // namespace graph

#endif // IDDFS_H_
