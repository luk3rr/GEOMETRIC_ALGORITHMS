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

#include "point.h"

namespace graph
{
    template<typename typeE, typename typeT, std::size_t nDim>
    class Edge;

    /**
     * @brief A class representing a vertex in a graph
     *
     * This class extends the `geom::Point` class to include additional properties
     * specific to vertices in a graph, such as an ID, current cost, edge connecting
     * to the successor and predecessor vertex, and an adjacency list
     *
     * @tparam typeV The type for the cost of reaching this vertex
     * @tparam typeT Type of the coordinates of the points (e.g., int, double, etc.).
     * @tparam nDim The dimensionality of the vertices
     * @tparam typeD Type of data stored in the vertex
     */
    template<typename typeV, typename typeT, std::size_t nDim, typename typeD = bool>
    class Vertex : public geom::Point<typeT, nDim>
    {
        private:
            std::size_t m_id; // Vertex ID

            // Current cost of the vertex. Optimization algorithms can use this variable
            // to store the total cost of reaching this vertex through a set of edges
            typeV    m_currentCost;
            double_t m_heuristicCost;

            typeD m_data; // Data stored in the vertex

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
             * @param data Data stored in the vertex
             */
            Vertex(std::size_t m_id, typeD data = typeD());

            /**
             * @brief Constructor overload
             * @param coordinates Point coordinates
             * @param id Vertex ID
             */
            Vertex(Vector<typeT> coordinates, std::size_t id, typeD data = typeD());

            ~Vertex();

            // Overload operators
            bool operator==(const Vertex<typeV, typeT, nDim, typeD>& other) const;
            bool operator<=(const Vertex<typeV, typeT, nDim, typeD>& other) const;
            bool operator>=(const Vertex<typeV, typeT, nDim, typeD>& other) const;
            bool operator<(const Vertex<typeV, typeT, nDim, typeD>& other) const;
            bool operator>(const Vertex<typeV, typeT, nDim, typeD>& other) const;

            /**
             * @brief Set a new value for the vertex ID
             * @param id New value for the vertex ID
             */
            void SetID(std::size_t id);

            /**
             * @brief Set a new value for the data stored in the vertex
             * @param data New value for the data stored in the vertex
             */
            void SetData(typeD data);

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
             * @return Data stored in the vertex
             */
            typeD GetData();

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

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    Vertex<typeV, typeT, nDim, typeD>::Vertex()
        : geom::Point<typeT, nDim>()
    {
        this->m_id            = 0;
        this->m_data          = typeD();
        this->m_currentCost   = 0;
        this->m_heuristicCost = 0;
        this->m_label         = 0;
        this->m_arrivalTime   = 0;
        this->m_departureTime = 0;
        this->m_successor     = nullptr;
        this->m_predecessor   = nullptr;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    Vertex<typeV, typeT, nDim, typeD>::Vertex(std::size_t id, typeD data)
        : geom::Point<typeT, nDim>()
    {
        this->m_id            = id;
        this->m_data          = data;
        this->m_currentCost   = 0;
        this->m_heuristicCost = 0;
        this->m_label         = 0;
        this->m_arrivalTime   = 0;
        this->m_departureTime = 0;
        this->m_successor     = nullptr;
        this->m_predecessor   = nullptr;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    Vertex<typeV, typeT, nDim, typeD>::Vertex(Vector<typeT> coordinates,
                                              std::size_t   id,
                                              typeD         data)
        : geom::Point<typeT, nDim>(coordinates)
    {
        this->m_id            = id;
        this->m_data          = data;
        this->m_currentCost   = 0;
        this->m_heuristicCost = 0;
        this->m_label         = 0;
        this->m_arrivalTime   = 0;
        this->m_departureTime = 0;
        this->m_successor     = nullptr;
        this->m_predecessor   = nullptr;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    Vertex<typeV, typeT, nDim, typeD>::~Vertex()
    { }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    bool Vertex<typeV, typeT, nDim, typeD>::operator==(
        const Vertex<typeV, typeT, nDim, typeD>& other) const
    {
        return this->m_currentCost == other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    bool Vertex<typeV, typeT, nDim, typeD>::operator<=(
        const Vertex<typeV, typeT, nDim, typeD>& other) const
    {
        return this->m_currentCost <= other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    bool Vertex<typeV, typeT, nDim, typeD>::operator>=(
        const Vertex<typeV, typeT, nDim, typeD>& other) const
    {
        return this->m_currentCost >= other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    bool Vertex<typeV, typeT, nDim, typeD>::operator<(
        const Vertex<typeV, typeT, nDim, typeD>& other) const
    {
        return this->m_currentCost < other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    bool Vertex<typeV, typeT, nDim, typeD>::operator>(
        const Vertex<typeV, typeT, nDim, typeD>& other) const
    {
        return this->m_currentCost > other.m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    void Vertex<typeV, typeT, nDim, typeD>::SetID(std::size_t id)
    {
        this->m_id = id;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    void Vertex<typeV, typeT, nDim, typeD>::SetData(typeD data)
    {
        this->m_data = data;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    void Vertex<typeV, typeT, nDim, typeD>::SetCurrentCost(typeV cost)
    {
        this->m_currentCost = cost;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    void Vertex<typeV, typeT, nDim, typeD>::SetHeuristicCost(double_t cost)
    {
        this->m_heuristicCost = cost;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    void
    Vertex<typeV, typeT, nDim, typeD>::SetEdge2Successor(Edge<typeV, typeT, nDim>* edge)
    {
        this->m_successor = edge;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    void Vertex<typeV, typeT, nDim, typeD>::SetEdge2Predecessor(
        Edge<typeV, typeT, nDim>* edge)
    {
        this->m_predecessor = edge;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    void Vertex<typeV, typeT, nDim, typeD>::SetLabel(uint32_t label)
    {
        this->m_label = label;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    void Vertex<typeV, typeT, nDim, typeD>::SetArrivalTime(uint32_t arrivalTime)
    {
        this->m_arrivalTime = arrivalTime;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    void Vertex<typeV, typeT, nDim, typeD>::SetDepartureTime(uint32_t departureTime)
    {
        this->m_departureTime = departureTime;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    uint32_t Vertex<typeV, typeT, nDim, typeD>::GetDegree()
    {
        return this->m_adjList.Size();
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    std::size_t Vertex<typeV, typeT, nDim, typeD>::GetID()
    {
        return this->m_id;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    typeD Vertex<typeV, typeT, nDim, typeD>::GetData()
    {
        return this->m_data;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    typeV Vertex<typeV, typeT, nDim, typeD>::GetCurrentCost() const
    {
        return this->m_currentCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    double_t Vertex<typeV, typeT, nDim, typeD>::GetHeuristicCost() const
    {
        return this->m_heuristicCost;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    Edge<typeV, typeT, nDim>* Vertex<typeV, typeT, nDim, typeD>::GetEdge2Successor()
    {
        return m_successor;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    Edge<typeV, typeT, nDim>* Vertex<typeV, typeT, nDim, typeD>::GetEdge2Predecessor()
    {
        return m_predecessor;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    uint32_t Vertex<typeV, typeT, nDim, typeD>::GetLabel() const
    {
        return this->m_label;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    uint32_t Vertex<typeV, typeT, nDim, typeD>::GetArrivalTime() const
    {
        return this->m_arrivalTime;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    uint32_t Vertex<typeV, typeT, nDim, typeD>::GetDepartureTime() const
    {
        return this->m_departureTime;
    }

    template<typename typeV, typename typeT, std::size_t nDim, typename typeD>
    Vector<Edge<typeV, typeT, nDim>*>&
    Vertex<typeV, typeT, nDim, typeD>::GetAdjacencyList()
    {
        return m_adjList;
    }

} // namespace graph

#endif // VERTEX_H_
