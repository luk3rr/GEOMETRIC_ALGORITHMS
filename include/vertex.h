/*
 * Filename: vertex.h
 * Created on: June  5, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <memory>

#include "vector.h"

#include "edge.h"
#include "point.h"

namespace graph
{
    /**
     * @brief A class representing a vertex in a graph
     *
     * This class extends the `geom::Point` class to include additional properties
     * specific to vertices in a graph, such as an ID, current cost, edge connecting
     * to the parent vertex, and an adjacency list
     *
     * @tparam typeV The type for the cost of reaching this vertex
     * @tparam typeT The data type to store vertex attributes
     * @tparam nDim The dimensionality of the vertices
     */
    template<typename typeV, typename typeT, std::size_t nDim>
    class Vertex : public geom::Point<typeT, nDim>
    {
        private:
            std::size_t m_id; // Vertex ID

            // Current cost of the vertex. Optimization algorithms can use this variable
            // to store the total cost of reaching this vertex through a set of edges
            typeV m_currentCost;

            // Edge connecting to the parent vertex
            Edge<typeV, typeT, nDim>* m_edge2parent;

            // Adjacency list
            Vector<Edge<typeV, typeT, nDim>*> m_adjList;

        public:
            Vertex();

            /**
             * @brief Constructor overload
             * @param id Vertex ID
             */
            Vertex(std::size_t m_id);

            /**
             * @brief Constructor overload
             * @param coordinates Point coordinates
             * @param id Vertex ID
             */
            Vertex(Vector<typeT> coordinates, std::size_t id);

            ~Vertex();

            // Overload operators
            bool operator==(const Vertex<typeV, typeT, nDim>& other) const;
            bool operator<=(const Vertex<typeV, typeT, nDim>& other) const;
            bool operator>=(const Vertex<typeV, typeT, nDim>& other) const;
            bool operator<(const Vertex<typeV, typeT, nDim>& other) const;
            bool operator>(const Vertex<typeV, typeT, nDim>& other) const;

            /**
             * @brief Set a new value for the vertex ID
             * @param id New value for the vertex ID
             */
            void SetID(std::size_t id);

            /**
             * @brief Set a new value for the vertex cost
             * @param cost New value for the vertex cost
             */
            void SetCurrentCost(typeV cost);

            /**
             * @brief Set the edge connecting to the parent vertex
             * @param edge A pointer to the edge connecting this vertex to its
             * parent
             */
            void SetEdge2Parent(Edge<typeV, typeT, nDim>* edge);

            /**
             * @brief Set the coordinates of the vertex
             * @param coordinates A vector representing the coordinates of the vertex
             */
            void SetCoordinates(Vector<typeT> coordinates);

            /**
             * @return Value of the vertex degree
             */
            uint32_t GetDegree();

            /**
             * @return Value of the vertex ID
             */
            std::size_t GetID();

            /**
             * @return Value of the vertex cost
             */
            typeV GetCurrentCost() const;

            /**
             * @return A pointer to the edge connecting this vertex to its parent
             */
            Edge<typeV, typeT, nDim>* GetEdge2Parent();

            /**
             * @return The coordinates of the vertex
             */
            Vector<typeT>& GetCoordinates();

            /**
             * @return Address of the adjacency list of this vertex
             */
            Vector<Edge<typeV, typeT, nDim>*>& GetAdjacencyList();
    };

    template<typename typeV, typename typeT, std::size_t nDim>
    Vertex<typeV, typeT, nDim>::Vertex() : geom::Point<typeT, nDim>()
    {
        this->m_id          = 0;
        this->m_currentCost = 0;
        this->m_edge2parent = nullptr;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Vertex<typeV, typeT, nDim>::Vertex(std::size_t id) : geom::Point<typeT, nDim>()
    {
        this->m_id          = id;
        this->m_currentCost = 0;
        this->m_edge2parent = nullptr;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Vertex<typeV, typeT, nDim>::Vertex(Vector<typeT> coordinates, std::size_t id)
        : geom::Point<typeT, nDim>(coordinates)
    {
        this->m_id          = id;
        this->m_currentCost = 0;
        this->m_edge2parent = nullptr;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Vertex<typeV, typeT, nDim>::~Vertex()
    {
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    bool Vertex<typeV, typeT, nDim>::operator==(
        const Vertex<typeV, typeT, nDim>& other) const
    {
        return this->m_currentCost == other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    bool Vertex<typeV, typeT, nDim>::operator<=(
        const Vertex<typeV, typeT, nDim>& other) const
    {
        return this->m_currentCost <= other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    bool Vertex<typeV, typeT, nDim>::operator>=(
        const Vertex<typeV, typeT, nDim>& other) const
    {
        return this->m_currentCost >= other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    bool
    Vertex<typeV, typeT, nDim>::operator<(const Vertex<typeV, typeT, nDim>& other) const
    {
        return this->m_currentCost < other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    bool
    Vertex<typeV, typeT, nDim>::operator>(const Vertex<typeV, typeT, nDim>& other) const
    {
        return this->m_currentCost > other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    void Vertex<typeV, typeT, nDim>::SetID(std::size_t id)
    {
        this->m_id = id;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    void Vertex<typeV, typeT, nDim>::SetCurrentCost(typeV cost)
    {
        this->m_currentCost = cost;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    void Vertex<typeV, typeT, nDim>::SetEdge2Parent(Edge<typeV, typeT, nDim>* edge)
    {
        this->m_edge2parent = edge;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    uint32_t Vertex<typeV, typeT, nDim>::GetDegree()
    {
        return this->m_adjList.Size();
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    std::size_t Vertex<typeV, typeT, nDim>::GetID()
    {
        return this->m_id;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    typeV Vertex<typeV, typeT, nDim>::GetCurrentCost() const
    {
        return this->m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Edge<typeV, typeT, nDim>* Vertex<typeV, typeT, nDim>::GetEdge2Parent()
    {
        return m_edge2parent;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Vector<Edge<typeV, typeT, nDim>*>& Vertex<typeV, typeT, nDim>::GetAdjacencyList()
    {
        return m_adjList;
    }

} // namespace graph

#endif // VERTEX_H_
