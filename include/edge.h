/*
 * Filename: edge.h
 * Created on: September 17, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef EDGE_H_
#define EDGE_H_

#include <cstddef>

#include "pair.h"

#include "line.h"
#include "vertex.h"

namespace graph
{
    /**
     * @brief Represents an edge in a graph in n-dimensional space.
     *
     * This class inherits from the geom::Line class and extends it to represent an edge
     * connecting two vertices in a graph. It stores information about the connected
     * vertices and the cost associated with the edge.
     *
     * @tparam typeE Type of the edge cost (e.g., int, double, etc.).
     * @tparam typeT Type of the coordinates of the points (e.g., int, double, etc.).
     * @tparam nDim The number of dimensions for the line (e.g., 2 for 2D, 3 for 3D).
     */
    template<typename typeE, typename typeT, std::size_t nDim>
    class Edge : public geom::Line<typeT, nDim>
    {
        private:
            // The cost of this edge
            typeE m_edgeCost;

        public:
            Edge(Vertex<typeE, typeT, nDim>* sideA, Vertex<typeE, typeT, nDim>* sideB);
            Edge(Vertex<typeE, typeT, nDim>* sideA,
                 Vertex<typeE, typeT, nDim>* sideB,
                 typeE                       edgeCost);

            ~Edge();

            /**
             * @brief Copy constructor
             */
            Edge(const Edge& other);

            /**
             * @brief Copy assignment operator
             **/
            Edge& operator=(const Edge& other);

            /**
             * @brief Overload operator <
             **/
            bool operator<(const Edge& other);

            /**
             * @brief Set a new cost of the edge
             **/
            void SetCost(typeE newCost);

            /**
             * @return Cost of the edge
             **/
            typeE GetCost();

            /**
             * @return Pair<a*, b*>, where a, b are pointers to vertex
             **/
            Pair<Vertex<typeE, typeT, nDim>*, Vertex<typeE, typeT, nDim>*>
            GetVertices();
    };

    template<typename typeE, typename typeT, std::size_t nDim>
    Edge<typeE, typeT, nDim>::Edge(Vertex<typeE, typeT, nDim>* sideA,
                                   Vertex<typeE, typeT, nDim>* sideB)
        : geom::Line<typeT, nDim>(*sideA, *sideB)
    {
        this->m_edgeCost = 0;
    }

    template<typename typeE, typename typeT, std::size_t nDim>
    Edge<typeE, typeT, nDim>::Edge(Vertex<typeE, typeT, nDim>* sideA,
                                   Vertex<typeE, typeT, nDim>* sideB,
                                   typeE                       edgeCost)
        : geom::Line<typeT, nDim>(*sideA, *sideB)
    {
        this->m_edgeCost = edgeCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim>
    Edge<typeE, typeT, nDim>::Edge(const Edge& other) : geom::Line<typeT, nDim>(other)

    {
        this->m_edgeCost = other.m_edgeCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim>
    Edge<typeE, typeT, nDim>::~Edge()
    {
    }

    template<typename typeE, typename typeT, std::size_t nDim>
    Edge<typeE, typeT, nDim>&
    Edge<typeE, typeT, nDim>::operator=(const Edge<typeE, typeT, nDim>& other)
    {
        if (this != &other)
        {
            geom::Line<typeT, nDim>::operator=(other);
            this->m_edgeCost = other.m_edgeCost;
        }

        return *this;
    }

    template<typename typeE, typename typeT, std::size_t nDim>
    bool Edge<typeE, typeT, nDim>::operator<(const Edge& other)
    {
        return this->m_edgeCost < other.m_edgeCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim>
    void Edge<typeE, typeT, nDim>::SetCost(typeE newCost)
    {
        this->m_edgeCost = newCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim>
    typeE Edge<typeE, typeT, nDim>::GetCost()
    {
        return this->m_edgeCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim>
    Pair<Vertex<typeE, typeT, nDim>*, Vertex<typeE, typeT, nDim>*>
    Edge<typeE, typeT, nDim>::GetVertices()
    {
        // Make dynamic cast to get correct data from base class
        return Pair<Vertex<typeE, typeT, nDim>*, Vertex<typeE, typeT, nDim>*>(
            dynamic_cast<Vertex<typeE, typeT, nDim>*>(this->GetA()),
            dynamic_cast<Vertex<typeE, typeT, nDim>*>(this->GetB()));
    }

} // namespace graph

#endif // EDGE_H_
