/*
 * Filename: graph.h
 * Created on: September 13, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <cstdio>

#include "vector.h"

#include "edge.h"
#include "vertex.h"

namespace graph
{
    /**
     * @brief A class representing a graph with vertices and edges, that is, G = (V,
     * E)
     *
     * @tparam typeG The type for the cost of the graph's edges
     * @tparam typeT The data type to store vertex and edge attributes
     * @tparam nDim The dimensionality of the vertices
     * @tparam directed Flag indicating whether the graph is directed (true) or
     * undirected (false)
     * @tparam typeD The type for the data stored in the vertices
     *
     * When the graph is undirected, two connected vertices store a copy of the same
     * edge, indicating that it is possible to travel from one to the other. The
     * edges store both ends as a Pair. In undirected graphs, the order of elements
     * in the pair is not considered.
     *
     * For directed graphs, only the starting vertex stores the edge. In this case,
     * the order in the pair is taken into account. For example, an edge a->b is
     * stored only in the adjacency list of vertex a, and its pair is pair<a, b>.
     */
    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed = false,
             typename typeD       = bool>
    class Graph
    {
        private:
            // Each vector position is the vertex ID
            Vector<Vertex<typeG, typeT, nDim, typeD>> m_vertices;

            // Store all edges created by this graph
            Vector<Edge<typeG, typeT, nDim, typeD>*> m_edges;

            // Number of vertices in the graph
            std::size_t m_numVertices;

        public:
            /**
             * @param numVertices Number of vertices in the graph
             * @param numEdges Number of edges in the graph
             **/
            Graph(std::size_t numVertices, std::size_t numEdges);

            ~Graph();

            /**
             * @brief Adds a vertex to the graph
             * @param vertex New vertex to be added to the graph
             **/
            void AddVertex(Vertex<typeG, typeT, nDim, typeD> vertex);

            /**
             * @brief Adds a edge
             * @param vertexID ID of the vertex that will receive a neighbor
             * @param neighborID ID of the neighbor
             * @param edgeCost Cost of the edge
             **/
            void AddEdge(std::size_t vertexID, std::size_t neighborID, typeG edgeCost);

            /**
             * @brief Adds a edge
             * @param vertexID ID of the vertex that will receive a neighbor
             * @param neighborID ID of the neighbor
             **/
            void AddEdge(std::size_t vertexID, std::size_t neighborID);

            /**
             * @brief Retrieves a reference to the vector of vertices
             * @return A reference to the vector containing all vertices in the graph
             **/
            Vector<Vertex<typeG, typeT, nDim, typeD>>& GetVertices();

            /**
             * @brief Retrieves a reference to the vector of edges
             * @return A reference to the vector containing all edges in the graph
             **/
            Vector<Edge<typeG, typeT, nDim, typeD>*>& GetEdges();

            /**
             * @brief Retrieves the number of vertices in the graph
             * @return The number of vertices in the graph
             **/
            std::size_t GetNumVertices() const;
    };

    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    Graph<typeG, typeT, nDim, directed, typeD>::Graph(std::size_t numVertices,
                                                      std::size_t numEdges)
    {
        // Resize the vector of vertices to allocate space for 'numVertices' elements,
        // allowing access using the [] operator.
        this->m_vertices.Resize(numVertices);

        // Reserve space in the vector of edges to optimize for 'numEdges' elements
        this->m_edges.Reserve(numEdges);

        this->m_numVertices = 0;
    }

    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    Graph<typeG, typeT, nDim, directed, typeD>::~Graph()
    {
        for (auto edge : this->m_edges)
        {
            delete edge;
        }
    }

    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    void Graph<typeG, typeT, nDim, directed, typeD>::AddVertex(
        Vertex<typeG, typeT, nDim, typeD> newVertex)
    {
        if (newVertex.GetID() >= this->m_vertices.Size())
        {
            m_vertices.Resize(newVertex.GetID() + 1);
        }

        this->m_vertices[newVertex.GetID()] = newVertex;
        this->m_numVertices++;
    }

    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    void Graph<typeG, typeT, nDim, directed, typeD>::AddEdge(std::size_t vertexID,
                                                             std::size_t neighborID,
                                                             typeG       edgeCost)
    {
        // Create a ptr for the edge
        Edge<typeG, typeT, nDim, typeD>* edge =
            new Edge<typeG, typeT, nDim, typeD>(&this->m_vertices[vertexID],
                                                &this->m_vertices[neighborID],
                                                edgeCost);

        // Add the edge to the neighbor list of vertexID
        this->m_vertices[vertexID].GetAdjacencyList().PushBack(edge);

        if (not directed)
            // Add the same edge to the neighbor list of neighborID, if graph is
            // undirected
            this->m_vertices[neighborID].GetAdjacencyList().PushBack(edge);

        // Store the edge to deallocate the memory later
        this->m_edges.PushBack(edge);
    }

    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    void Graph<typeG, typeT, nDim, directed, typeD>::AddEdge(std::size_t vertexID,
                                                             std::size_t neighborID)
    {
        this->AddEdge(vertexID, neighborID, 0);
    }

    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    Vector<Vertex<typeG, typeT, nDim, typeD>>&
    Graph<typeG, typeT, nDim, directed, typeD>::GetVertices()
    {
        return this->m_vertices;
    }

    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    Vector<Edge<typeG, typeT, nDim, typeD>*>&
    Graph<typeG, typeT, nDim, directed, typeD>::GetEdges()
    {
        return this->m_edges;
    }

    template<typename typeG,
             typename typeT,
             std::size_t nDim,
             bool        directed,
             typename typeD>
    std::size_t Graph<typeG, typeT, nDim, directed, typeD>::GetNumVertices() const
    {
        return this->m_numVertices;
    }

} // namespace graph

#endif // GRAPH_H_
