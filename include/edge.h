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
     * @tparam typeD Type of the data stored in the vertices (e.g., int, double, vector,
     * etc.).
     */
    template<typename typeE, typename typeT, std::size_t nDim, typename typeD = bool>
    class Edge : public geom::Line<typeT, nDim>
    {
        private:
            // The cost of this edge
            typeE m_edgeCost;

        public:
            Edge(Vertex<typeE, typeT, nDim, typeD>* sideA,
                 Vertex<typeE, typeT, nDim, typeD>* sideB);
            Edge(Vertex<typeE, typeT, nDim, typeD>* sideA,
                 Vertex<typeE, typeT, nDim, typeD>* sideB,
                 typeE                              edgeCost);

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
            Pair<Vertex<typeE, typeT, nDim, typeD>*, Vertex<typeE, typeT, nDim, typeD>*>
            GetVertices();
    };

    template<typename typeE, typename typeT, std::size_t nDim, typename typeD>
    Edge<typeE, typeT, nDim, typeD>::Edge(Vertex<typeE, typeT, nDim, typeD>* sideA,
                                          Vertex<typeE, typeT, nDim, typeD>* sideB)
        : geom::Line<typeT, nDim>(*sideA, *sideB)
    {
        this->m_edgeCost = 0;
    }

    template<typename typeE, typename typeT, std::size_t nDim, typename typeD>
    Edge<typeE, typeT, nDim, typeD>::Edge(Vertex<typeE, typeT, nDim, typeD>* sideA,
                                          Vertex<typeE, typeT, nDim, typeD>* sideB,
                                          typeE                              edgeCost)
        : geom::Line<typeT, nDim>(*sideA, *sideB)
    {
        this->m_edgeCost = edgeCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim, typename typeD>
    Edge<typeE, typeT, nDim, typeD>::Edge(const Edge& other)
        : geom::Line<typeT, nDim>(other)

    {
        this->m_edgeCost = other.m_edgeCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim, typename typeD>
    Edge<typeE, typeT, nDim, typeD>::~Edge()
    { }

    template<typename typeE, typename typeT, std::size_t nDim, typename typeD>
    Edge<typeE, typeT, nDim, typeD>& Edge<typeE, typeT, nDim, typeD>::operator=(
        const Edge<typeE, typeT, nDim, typeD>& other)
    {
        if (this != &other)
        {
            geom::Line<typeT, nDim>::operator=(other);
            this->m_edgeCost = other.m_edgeCost;
        }

        return *this;
    }

    template<typename typeE, typename typeT, std::size_t nDim, typename typeD>
    bool Edge<typeE, typeT, nDim, typeD>::operator<(const Edge& other)
    {
        return this->m_edgeCost < other.m_edgeCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim, typename typeD>
    void Edge<typeE, typeT, nDim, typeD>::SetCost(typeE newCost)
    {
        this->m_edgeCost = newCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim, typename typeD>
    typeE Edge<typeE, typeT, nDim, typeD>::GetCost()
    {
        return this->m_edgeCost;
    }

    template<typename typeE, typename typeT, std::size_t nDim, typename typeD>
    Pair<Vertex<typeE, typeT, nDim, typeD>*, Vertex<typeE, typeT, nDim, typeD>*>
    Edge<typeE, typeT, nDim, typeD>::GetVertices()
    {
        // Make dynamic cast to get correct data from base class
        return Pair<Vertex<typeE, typeT, nDim, typeD>*,
                    Vertex<typeE, typeT, nDim, typeD>*>(
            dynamic_cast<Vertex<typeE, typeT, nDim, typeD>*>(this->GetA()),
            dynamic_cast<Vertex<typeE, typeT, nDim, typeD>*>(this->GetB()));
    }

} // namespace graph

#endif // EDGE_H_
