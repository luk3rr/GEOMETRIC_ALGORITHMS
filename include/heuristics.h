/*
 * Filename: heuristics.h
 * Created on: April 11, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef HEURISTICS_H_
#define HEURISTICS_H_

#include <cmath>
#include <cstddef>

#include "vertex.h"

namespace heuristics
{
    namespace distance
    {
        /**
         * @brief Euclidean distance between two vertices
         * @param source Pointer to the source vertex
         * @param target Pointer to the target vertex
         */
        template<typename typeG, typename typeT, std::size_t nDim>
        double_t Euclidean(graph::Vertex<typeG, typeT, nDim>* source,
                           graph::Vertex<typeG, typeT, nDim>* target)
        {
            double_t sum = 0;
            for (std::size_t i = 0; i < nDim; i++)
            {
                sum += std::pow(source->GetCoordinates().At(i) -
                                    target->GetCoordinates().At(i),
                                2);
            }
            return std::sqrt(sum);
        }

        /**
         * @brief Manhattan distance between two vertices
         * @param source Pointer to the source vertex
         * @param target Pointer to the target vertex
         */
        template<typename typeG, typename typeT, std::size_t nDim>
        inline double_t Manhattan(graph::Vertex<typeG, typeT, nDim>* source,
                                  graph::Vertex<typeG, typeT, nDim>* target)
        {
            double_t sum = 0;
            for (std::size_t i = 0; i < nDim; i++)
            {
                sum += std::abs(source->GetCoordinates().At(i) -
                                target->GetCoordinates().At(i));
            }
            return sum;
        }

        /**
         * @brief Minkowski distance between two vertices
         * @param source Pointer to the source vertex
         * @param target Pointer to the target vertex
         * @param p Exponent of the Minkowski distance
         */
        template<typename typeG, typename typeT, std::size_t nDim>
        inline double_t Minkowski(graph::Vertex<typeG, typeT, nDim>* source,
                                  graph::Vertex<typeG, typeT, nDim>* target,
                                  double_t                           p)
        {
            double_t sum = 0;
            for (std::size_t i = 0; i < nDim; i++)
            {
                sum += std::pow(std::abs(source->GetCoordinates().At(i) -
                                         target->GetCoordinates().At(i)),
                                p);
            }

            return std::pow(sum, 1 / p);
        }

        /**
         * @brief Hamming distance between two vertices
         * @param source Pointer to the source vertex
         * @param target Pointer to the target vertex
         */
        template<typename typeG, typename typeT, std::size_t nDim>
        inline double_t Hamming(graph::Vertex<typeG, typeT, nDim>* source,
                                graph::Vertex<typeG, typeT, nDim>* target)
        {
            double_t sum = 0;
            for (std::size_t i = 0; i < nDim; i++)
            {
                sum += source->GetCoordinates().At(i) != target->GetCoordinates().At(i);
            }
            return sum;
        }

    } // namespace distance

} // namespace heuristics

#endif // HEURISTICS_H_
