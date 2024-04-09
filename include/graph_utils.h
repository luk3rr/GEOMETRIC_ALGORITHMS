/*
 * Filename: graph_utils.h
 * Created on: November  2, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef GRAPH_UTILS_H_
#define GRAPH_UTILS_H_

#include <cstddef>
#include <limits>

#include "vector.h"

#include "edge.h"
#include "graph.h"

namespace graph
{

    /**
     * @brief A utility class providing various auxiliary functions for graph
     * operations.
     *
     * @tparam typeG The type for the cost of the graph's edges
     * @tparam typeT The data type to store vertex and edge attributes
     * @tparam nDim The dimensionality of the vertices
     * @tparam directed Flag indicating whether the graph is directed (true) or
     * undirected (false)
     */
    template<typename typeG, typename typeT, std::size_t nDim, bool directed = false>
    class Utils
    {
        public:
            /**
             * @brief Relax the edge (u, v)
             * @param u, v Pointers to vertices of this edge
             * @param uv Pointer to the edge (u, v)
             * @return True if edge was relaxed, False otherwise
             **/
            static bool Relax(Vertex<typeG, typeT, nDim>* u,
                              Vertex<typeG, typeT, nDim>* v,
                              Edge<typeG, typeT, nDim>*   uv);

            /**
             * @brief Run Dijkstra's algorithm to find the shortest paths from a given
             *        source vertex
             * @param graph The graph on which to calculate the shortest paths
             * @param sourceID The source vertex id from which to calculate the shortest
             *        paths
             **/
            static void Dijkstra(Graph<typeG, typeT, nDim>& graph,
                                 std::size_t                sourceID);

            /**
             * @brief Run Prim's algorithm to find Minimum Spanning Tree starting from a
             *        given source vertex
             * @param graph The graph on which to calculate the MST
             * @param sourceID The source vertex id from which to begin the MST
             *        calculation
             **/
            static void Prim(Graph<typeG, typeT, nDim>& graph, std::size_t sourceID);

            struct ComparePtrVertex
            {
                    bool operator()(const Vertex<typeG, typeT, nDim>* v1,
                                    const Vertex<typeG, typeT, nDim>* v2) const
                    {
                        return v1->GetCurrentCost() <= v2->GetCurrentCost();
                    }
            };

            struct ComparePtrEdge
            {
                    bool operator()(const Edge<typeG, typeT, nDim>* e1,
                                    const Edge<typeG, typeT, nDim>* e2) const
                    {
                        return e1->GetCost() <= e2->GetCost();
                    }
            };
    };

    template<typename typeG, typename typeT, std::size_t nDim, bool directed>
    bool Utils<typeG, typeT, nDim, directed>::Relax(Vertex<typeG, typeT, nDim>* u,
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

    template<typename typeG, typename typeT, std::size_t nDim, bool directed>
    void Utils<typeG, typeT, nDim, directed>::Dijkstra(Graph<typeG, typeT, nDim>& graph,
                                                       std::size_t sourceID)

    {
        bheap::PriorityQueue<Vertex<typeG, typeT, nDim>*, ComparePtrVertex> minPQueue;

        // Defines the infinity value for the typeG type
        typeG INFINITY_VALUE = std::numeric_limits<typeG>::max();

        // Initialize all vertex costs to infinity
        for (std::size_t i = 0; i < graph.GetVertices().Size(); i++)
        {
            if (i != sourceID)
                graph.GetVertices().At(i).SetCurrentCost(INFINITY_VALUE);

            graph.GetVertices().At(i).SetEdge2Predecessor(nullptr);
        }

        graph.GetVertices().At(sourceID).SetCurrentCost(0);

        minPQueue.Enqueue(&graph.GetVertices().At(sourceID));

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, nDim>* u = nullptr;
        Vertex<typeG, typeT, nDim>* v = nullptr;

        Edge<typeG, typeT, nDim>* uv;

        Vector<Edge<typeG, typeT, nDim>*> uAdjList;

        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();

            uAdjList = u->GetAdjacencyList();

            for (std::size_t i = 0; i < uAdjList.Size(); i++)
            {
                // Edge uv (or vu, if is non-directed)
                uv = uAdjList.At(i);

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertices()[uv->GetVertices().GetSecond()->GetID()]
                    : v = &graph.GetVertices()[uv->GetVertices().GetFirst()->GetID()];

                if (Relax(u, v, uAdjList.At(i)))
                {
                    // If the neighbor's cost is updated, then add again to queue to
                    // update all neighbors with new cost
                    minPQueue.Enqueue(v);
                }
            }
        }
    }

    template<typename typeG, typename typeT, std::size_t nDim, bool directed>
    void Utils<typeG, typeT, nDim, directed>::Prim(Graph<typeG, typeT, nDim>& graph,
                                                   std::size_t                sourceID)
    {
        bheap::PriorityQueue<Vertex<typeG, typeT, nDim>*, ComparePtrVertex> minPQueue;

        // Defines the infinity value for the typeG type
        typeG INFINITY_VALUE = std::numeric_limits<typeG>::max();

        // Initialize all vertex costs to infinity
        for (std::size_t i = 0; i < graph.GetVertices().Size(); i++)
        {
            if (i != sourceID)
                graph.GetVertices().At(i).SetCurrentCost(INFINITY_VALUE);

            graph.GetVertices().At(i).SetEdge2Predecessor(nullptr);
        }

        // Auxiliar variables to make code most legible
        Vertex<typeG, typeT, nDim>* u  = nullptr;
        Vertex<typeG, typeT, nDim>* v  = nullptr;
        Edge<typeG, typeT, nDim>*   uv = nullptr;

        Vector<Edge<typeG, typeT, nDim>*> uAdjList;

        // A vector to track whether a vertex with ID as the index has been visited or
        // not
        Vector<bool> inMst(graph.GetVertices().Size(), false);

        minPQueue.Enqueue(&graph.GetVertices().At(sourceID));

        Vector<Vertex<typeG, typeT, nDim>*> aux;

        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();

            uAdjList = u->GetAdjacencyList();

            for (std::size_t i = 0; i < uAdjList.Size(); i++)
            {
                // Edge uv (or vu, if is non-directed)
                uv = uAdjList.At(i);

                // Get the pointer do neighbor vertex, since one end of the edge is
                // vertex u, and the other end is vertex v
                uv->GetVertices().GetFirst()->GetID() == u->GetID()
                    ? v = &graph.GetVertices()[uv->GetVertices().GetSecond()->GetID()]
                    : v = &graph.GetVertices()[uv->GetVertices().GetFirst()->GetID()];

                // Check if the neighbor vertex 'v' is not in the Minimum Spanning Tree
                // (MST) and if the cost of the edge 'uv' is less than the current cost
                // of 'v'
                if (not inMst[v->GetID()] and uv->GetCost() < v->GetCurrentCost())
                {
                    // Update the cost of 'v' and enqueue it to reposition it in the
                    // queue based on the new cost
                    v->SetEdge2Predecessor(uv);
                    v->SetCurrentCost(uv->GetCost());
                    minPQueue.Enqueue(v);
                }
            }

            // Set 'u' as checked
            inMst[u->GetID()] = true;
        }
    }
} // namespace graph

#endif // GRAPH_UTILS_H_
