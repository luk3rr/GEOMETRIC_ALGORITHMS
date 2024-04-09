/*
 * Filename: graph_utils.h
 * Created on: November  2, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef GRAPH_UTILS_H_
#define GRAPH_UTILS_H_

#include <cstddef>

#include "edge.h"

/**
 * @brief A utility namespace providing various auxiliary functions for graph
 * operations.
 *
 * @tparam typeG The type for the cost of the graph's edges
 * @tparam typeT The data type to store vertex and edge attributes
 * @tparam nDim The dimensionality of the vertices
 * @tparam directed Flag indicating whether the graph is directed (true) or
 * undirected (false)
 */
namespace graph
{
    template<typename typeG, typename typeT, std::size_t nDim>
    struct ComparePtrVertex
    {
            bool operator()(const Vertex<typeG, typeT, nDim>* v1,
                            const Vertex<typeG, typeT, nDim>* v2) const
            {
                return v1->GetCurrentCost() <= v2->GetCurrentCost();
            }
    };

    template<typename typeG, typename typeT, std::size_t nDim>
    struct ComparePtrEdge
    {
            bool operator()(const Edge<typeG, typeT, nDim>* e1,
                            const Edge<typeG, typeT, nDim>* e2) const
            {
                return e1->GetCost() <= e2->GetCost();
            }
    };

    /**
     * @brief Relax the edge (u, v)
     * @param u, v Pointers to vertices of this edge
     * @param uv Pointer to the edge (u, v)
     * @return True if edge was relaxed, False otherwise
     **/
    template<typename typeG, typename typeT, std::size_t nDim>
    inline bool Relax(Vertex<typeG, typeT, nDim>* u,
                      Vertex<typeG, typeT, nDim>* v,
                      Edge<typeG, typeT, nDim>*   uv)
    {
        if (v->GetCurrentCost() > (u->GetCurrentCost() + uv->GetCost()))
        {
            v->SetCurrentCost(u->GetCurrentCost() + uv->GetCost());
            v->SetEdge2Predecessor(uv);
            return true;
        }

        return false;
    }

} // namespace graph

#endif // GRAPH_UTILS_H_
