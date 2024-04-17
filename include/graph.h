/*
 * Filename: graph.h
 * Created on: September 13, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <cstdio>
#include <iostream>

#include "vector.h"

#include "edge.h"
#include "map.h"
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
             typename typeD       = bool,
             std::size_t nDim     = 2,
             bool        directed = false>
    class Graph
    {
        private:
            // Store all vertices created by this graph in a map
            rbtree::Map<std::size_t, Vertex<typeG, typeT, typeD, nDim>> m_vertices;
            rbtree::Map<std::size_t, Edge<typeG, typeT, typeD, nDim>*>  m_edges;

            // Store all edges created by this graph
            // Vector<Edge<typeG, typeT, typeD, nDim>*> m_edges;

        public:
            Graph();

            ~Graph();

            /**
             * @brief Adds a vertex to the graph
             * @param vertex New vertex to be added to the graph
             **/
            void AddVertex(Vertex<typeG, typeT, typeD, nDim> vertex);

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
             * @brief Removes a vertex from the graph
             * @param vertexID ID of the vertex to be removed
             * @return True if the vertex was removed, false otherwise
             **/
            bool RemoveVertex(std::size_t vertexID);

            /**
             * @brief Removes an edge from the graph
             * @param edgeID ID of the edge to be removed
             * @return True if the edge was removed, false otherwise
             **/
            bool RemoveEdge(std::size_t edgeID);

            /**
             * @brief Retrieves a reference to the map of vertices
             * @return A reference to the map containing all vertices in the graph
             **/
            rbtree::Map<std::size_t, Vertex<typeG, typeT, typeD, nDim>>& GetVertices();

            /**
             * @brief Retrieves a reference to the vector of edges
             * @return A reference to the vector containing all edges in the graph
             **/
            rbtree::Map<std::size_t, Edge<typeG, typeT, typeD, nDim>*>& GetEdges();

            /**
             * @brief Retrieves a reference to a vertex with a given ID
             * @param vertexID ID of the vertex to be retrieved
             * @return A reference to the vertex with the given ID
             **/
            Vertex<typeG, typeT, typeD, nDim>& GetVertex(std::size_t vertexID);

            /**
             * @brief Retrieves a reference to an edge with a given ID
             * @param edgeID ID of the edge to be retrieved
             * @return A reference to the edge with the given ID
             **/
            Edge<typeG, typeT, typeD, nDim>& GetEdge(std::size_t edgeID);

            /**
             * @brief Retrieves the number of vertices in the graph
             * @return The number of vertices in the graph
             **/
            std::size_t GetNumVertices() const;

            /**
             * @brief Retrieves the number of edges in the graph
             * @return The number of edges in the graph
             **/
            std::size_t GetNumEdges() const;

            /**
             * @brief Checks if the graph contains a vertex with a given ID
             * @param vertexID ID of the vertex to be checked
             * @return True if the graph contains the vertex, false otherwise
             **/
            bool ContainsVertex(std::size_t vertexID);

            /**
             * @brief Checks if the graph contains an edge with a given ID
             * @param edgeID ID of the edge to be checked
             * @return True if the graph contains the edge, false otherwise
             **/
            bool ContainsEdge(std::size_t edgeID);

            /**
             * @brief Destroys the graph, deallocating all edges
             **/
            void Destroy();
    };

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    Graph<typeG, typeT, typeD, nDim, directed>::Graph()
    { }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    Graph<typeG, typeT, typeD, nDim, directed>::~Graph()
    {
        this->Destroy();
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    void Graph<typeG, typeT, typeD, nDim, directed>::AddVertex(
        Vertex<typeG, typeT, typeD, nDim> newVertex)
    {
        this->m_vertices.Insert(newVertex.GetID(), newVertex);
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    void Graph<typeG, typeT, typeD, nDim, directed>::AddEdge(std::size_t vertexID,
                                                             std::size_t neighborID,
                                                             typeG       edgeCost)
    {
        // Create a ptr for the edge
        Edge<typeG, typeT, typeD, nDim>* edge =
            new Edge<typeG, typeT, typeD, nDim>(&this->m_vertices[vertexID],
                                                &this->m_vertices[neighborID],
                                                this->m_edges.Size(),
                                                edgeCost);

        // Add the edge to the neighbor list of vertexID
        this->m_vertices[vertexID].GetAdjacencyList().Insert(edge->GetID(), edge);

        if (not directed)
            // Add the same edge to the neighbor list of neighborID, if graph is
            // undirected
            this->m_vertices[neighborID].GetAdjacencyList().Insert(edge->GetID(), edge);

        // Store the edge to deallocate the memory later
        this->m_edges.Insert(edge->GetID(), edge);
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    void Graph<typeG, typeT, typeD, nDim, directed>::AddEdge(std::size_t vertexID,
                                                             std::size_t neighborID)
    {
        this->AddEdge(vertexID, neighborID, 0);
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    bool Graph<typeG, typeT, typeD, nDim, directed>::RemoveVertex(std::size_t vertexID)
    {

        if (not this->m_vertices.Contains(vertexID))
            return false;

        Vertex<typeG, typeT, typeD, nDim>* u = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v = nullptr;

        u = &this->m_vertices[vertexID];

        // Remove all edges that have vertexID as a neighbor
        for (auto& edge : u->GetAdjacencyList())
        {
            this->m_edges.Remove(edge.GetFirst());
        }

        // Remove the vertex from the graph
        this->m_vertices.Remove(vertexID);

        return true;
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    bool Graph<typeG, typeT, typeD, nDim, directed>::RemoveEdge(std::size_t edgeID)
    {

        if (not this->m_edges.Contains(edgeID))
            return false;

        Edge<typeG, typeT, typeD, nDim>*   edge = &this->m_edges[edgeID];
        Vertex<typeG, typeT, typeD, nDim>* u    = nullptr;
        Vertex<typeG, typeT, typeD, nDim>* v    = nullptr;

        // Remove the edge from u
        u->GetAdjacencyList().Remove(edge->GetID());

        // if the graph is undirected, remove the edge from v,
        // since the edge is shared by both vertices
        if (not directed)
        {
            // Get the neighbor vertex
            edge->GetVertices().GetFirst()->GetID() == u->GetID()
                ? v = &this->m_vertices[edge->GetVertices().GetSecond()->GetID()]
                : v = &this->m_vertices[edge->GetVertices().GetFirst()->GetID()];

            v->GetAdjacencyList().Remove(edge->GetID());
        }

        // Remove the edge from the graph
        delete this->m_edges.Get(edge->GetID());
        this->m_edges.Remove(edgeID);

        return true;
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    rbtree::Map<std::size_t, Vertex<typeG, typeT, typeD, nDim>>&
    Graph<typeG, typeT, typeD, nDim, directed>::GetVertices()
    {
        return this->m_vertices;
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    rbtree::Map<std::size_t, Edge<typeG, typeT, typeD, nDim>*>&
    Graph<typeG, typeT, typeD, nDim, directed>::GetEdges()
    {
        return this->m_edges;
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    Vertex<typeG, typeT, typeD, nDim>&
    Graph<typeG, typeT, typeD, nDim, directed>::GetVertex(std::size_t vertexID)
    {
        try
        {
            return this->m_vertices.Get(vertexID);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Vertex with ID " << vertexID << " not found" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    Edge<typeG, typeT, typeD, nDim>&
    Graph<typeG, typeT, typeD, nDim, directed>::GetEdge(std::size_t edgeID)
    {
        try
        {
            return this->m_edges.Get(edgeID);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Edge with ID " << edgeID << " not found" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    std::size_t Graph<typeG, typeT, typeD, nDim, directed>::GetNumVertices() const
    {
        return this->m_vertices.Size();
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    std::size_t Graph<typeG, typeT, typeD, nDim, directed>::GetNumEdges() const
    {
        return this->m_edges.Size();
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    bool Graph<typeG, typeT, typeD, nDim, directed>::ContainsVertex(
        std::size_t vertexID)
    {
        return this->m_vertices.Contains(vertexID);
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    bool
    Graph<typeG, typeT, typeD, nDim, directed>::ContainsEdge(std::size_t edgeID)
    {
        return this->m_edges.Contains(edgeID);
    }

    template<typename typeG,
             typename typeT,
             typename typeD,
             std::size_t nDim,
             bool        directed>
    void Graph<typeG, typeT, typeD, nDim, directed>::Destroy()
    {
        for (auto& edge : this->m_edges)
            delete edge.GetSecond();

        this->m_vertices.Clear();
        this->m_edges.Clear();
    }

} // namespace graph

#endif // GRAPH_H_
