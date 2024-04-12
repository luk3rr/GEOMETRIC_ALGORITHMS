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
     * to the successor and predecessor vertex, and an adjacency list
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
            typeV    m_currentCost;
            double_t m_heuristicCost;

            // Edge connecting to the successor and predecessor vertex
            Edge<typeV, typeT, nDim>* m_successor;
            Edge<typeV, typeT, nDim>* m_predecessor;

            uint32_t m_label;         // Vertex label
            uint32_t m_arrivalTime;   // Arrival time of the vertex
            uint32_t m_departureTime; // Departure time of the vertex

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
             * @brief Set a new value for the vertex heuristic cost
             * @param cost New value for the vertex heuristic cost
             */
            void SetHeuristicCost(double_t cost);

            /**
             * @brief Set the edge connecting to the successor vertex
             * @param edge A pointer to the edge connecting this vertex to its
             * successor
             */
            void SetEdge2Successor(Edge<typeV, typeT, nDim>* edge);

            /**
             * @brief Set the edge connecting to the predecessor vertex
             * @param edge A pointer to the edge connecting this vertex to its
             * predecessor
             */
            void SetEdge2Predecessor(Edge<typeV, typeT, nDim>* edge);

            /**
             * @brief Set the label of the vertex
             * @param label New value for the vertex label
             */
            void SetLabel(uint32_t label);

            /**
             * @brief Set the arrival time of the vertex
             * @param arrivalTime New value for the arrival time
             */
            void SetArrivalTime(uint32_t arrivalTime);

            /**
             * @brief Set the departure time of the vertex
             * @param departureTime New value for the departure time
             */
            void SetDepartureTime(uint32_t departureTime);

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
             * @return Value of the vertex heuristic cost
             */
            double_t GetHeuristicCost() const;

            /**
             * @return A pointer to the edge connecting this vertex to its successor
             * vertex
             */
            Edge<typeV, typeT, nDim>* GetEdge2Successor();

            /**
             * @return A pointer to the edge connecting this vertex to its predecessor
             * vertex
             */
            Edge<typeV, typeT, nDim>* GetEdge2Predecessor();

            /**
             * @return The label of the vertex
             */
            uint32_t GetLabel() const;

            /**
             * @return The arrival time of the vertex
             */
            uint32_t GetArrivalTime() const;

            /**
             * @return The departure time of the vertex
             */
            uint32_t GetDepartureTime() const;

            /**
             * @return Address of the adjacency list of this vertex
             */
            Vector<Edge<typeV, typeT, nDim>*>& GetAdjacencyList();
    };

    template<typename typeV, typename typeT, std::size_t nDim>
    Vertex<typeV, typeT, nDim>::Vertex()
        : geom::Point<typeT, nDim>()
    {
        this->m_id            = 0;
        this->m_currentCost   = 0;
        this->m_heuristicCost = 0;
        this->m_label         = 0;
        this->m_arrivalTime   = 0;
        this->m_departureTime = 0;
        this->m_successor     = nullptr;
        this->m_predecessor   = nullptr;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Vertex<typeV, typeT, nDim>::Vertex(std::size_t id)
        : geom::Point<typeT, nDim>()
    {
        this->m_id            = id;
        this->m_currentCost   = 0;
        this->m_heuristicCost = 0;
        this->m_label         = 0;
        this->m_arrivalTime   = 0;
        this->m_departureTime = 0;
        this->m_successor     = nullptr;
        this->m_predecessor   = nullptr;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Vertex<typeV, typeT, nDim>::Vertex(Vector<typeT> coordinates, std::size_t id)
        : geom::Point<typeT, nDim>(coordinates)
    {
        this->m_id            = id;
        this->m_currentCost   = 0;
        this->m_heuristicCost = 0;
        this->m_label         = 0;
        this->m_arrivalTime   = 0;
        this->m_departureTime = 0;
        this->m_successor     = nullptr;
        this->m_predecessor   = nullptr;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Vertex<typeV, typeT, nDim>::~Vertex()
    { }

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
    void Vertex<typeV, typeT, nDim>::SetHeuristicCost(double_t cost)
    {
        this->m_heuristicCost = cost;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    void Vertex<typeV, typeT, nDim>::SetEdge2Successor(Edge<typeV, typeT, nDim>* edge)
    {
        this->m_successor = edge;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    void Vertex<typeV, typeT, nDim>::SetEdge2Predecessor(Edge<typeV, typeT, nDim>* edge)
    {
        this->m_predecessor = edge;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    void Vertex<typeV, typeT, nDim>::SetLabel(uint32_t label)
    {
        this->m_label = label;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    void Vertex<typeV, typeT, nDim>::SetArrivalTime(uint32_t arrivalTime)
    {
        this->m_arrivalTime = arrivalTime;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    void Vertex<typeV, typeT, nDim>::SetDepartureTime(uint32_t departureTime)
    {
        this->m_departureTime = departureTime;
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
    double_t Vertex<typeV, typeT, nDim>::GetHeuristicCost() const
    {
        return this->m_heuristicCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Edge<typeV, typeT, nDim>* Vertex<typeV, typeT, nDim>::GetEdge2Successor()
    {
        return m_successor;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Edge<typeV, typeT, nDim>* Vertex<typeV, typeT, nDim>::GetEdge2Predecessor()
    {
        return m_predecessor;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    uint32_t Vertex<typeV, typeT, nDim>::GetLabel() const
    {
        return this->m_label;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    uint32_t Vertex<typeV, typeT, nDim>::GetArrivalTime() const
    {
        return this->m_arrivalTime;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    uint32_t Vertex<typeV, typeT, nDim>::GetDepartureTime() const
    {
        return this->m_departureTime;
    }

    template<typename typeV, typename typeT, std::size_t nDim>
    Vector<Edge<typeV, typeT, nDim>*>& Vertex<typeV, typeT, nDim>::GetAdjacencyList()
    {
        return m_adjList;
    }

} // namespace graph

#endif // VERTEX_H_
