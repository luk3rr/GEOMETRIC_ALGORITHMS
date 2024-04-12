/*
 * Filename: graph_utils.h
 * Created on: November  2, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef GRAPH_UTILS_H_
#define GRAPH_UTILS_H_

#include <cstddef>
#include <cstdint>

#include "edge.h"
#include "graph.h"
#include "vector.h"
#include "heuristics.h"

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
        // Heuristic by default is 0
        if (v->GetCurrentCost() >
            ((u->GetCurrentCost() - u->GetHeuristicCost()) + uv->GetCost()))
        {
            v->SetCurrentCost((u->GetCurrentCost() - u->GetHeuristicCost()) +
                              uv->GetCost() + v->GetHeuristicCost());

            v->SetEdge2Predecessor(uv);
            return true;
        }

        return false;
    }


    namespace
    {
        template<typename typeG, typename typeT, std::size_t nDim>
        inline double_t CalculateHeuristic(heuristics::distance::Heuristic heuristic,
                                           Vertex<typeG, typeT, nDim>*     u,
                                           Vertex<typeG, typeT, nDim>*     v)
        {
            switch (heuristic)
            {
                case heuristics::distance::Heuristic::MANHATTAN:
                    return heuristics::distance::Manhattan(u, v);

                case heuristics::distance::Heuristic::EUCLIDEAN:
                    return heuristics::distance::Euclidean(u, v);

                case heuristics::distance::Heuristic::MINKOWSKI:
                    return heuristics::distance::Minkowski(u, v);

                case heuristics::distance::Heuristic::HAMMING:
                    return heuristics::distance::Hamming(u, v);

                default:
                    std::cerr << "Invalid heuristic function. Using Euclidean distance "
                                 "as default."
                              << std::endl;
                    return heuristics::distance::Euclidean(u, v);
            }
        }
    } // namespace


    template<typename typeG, typename typeT, std::size_t nDim>
    inline void PrintPath(Graph<typeG, typeT, nDim>&  graph,
                          Vertex<typeG, typeT, nDim>* v)
    {
        // Create a vector to store the path
        Vector<uint32_t> path;

        Edge<typeG, typeT, nDim>* uv;

        path.PushBack(v->GetID());
        // Get the path
        while ((uv = v->GetEdge2Predecessor()))
        {
            uv->GetVertices().GetFirst()->GetID() == v->GetID()
                ? v = &graph.GetVertices()[uv->GetVertices().GetSecond()->GetID()]
                : v = &graph.GetVertices()[uv->GetVertices().GetFirst()->GetID()];

            path.PushBack(v->GetID());
        }

        // Print the path
        std::cout << "Path: ";
        for (int32_t i = path.Size() - 1; i >= 0; i--)
        {
            if (i == 0)
                std::cout << path[i] << std::endl;
            else
                std::cout << path[i] << " -> ";
        }
    }
} // namespace graph

#endif // GRAPH_UTILS_H_
