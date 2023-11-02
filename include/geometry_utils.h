/*
 * Filename: geometry_utils.h
 * Created on: June  7, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <numbers>

#include "vector.h"

#include "point.h"

// Gera um número no intervalo [min, max]
#define GEN_NUM std::rand() % (max - min + 1) + min
#define PI std::numbers::pi

namespace geom
{
    enum PointOrientation
    {
        CLOCKWISE = 1,
        ANTICLOCKWISE = -1,
        COLLINEAR = 0
    };

    /**
     * @brief A utility class providing various auxiliary functions for geometric
     * computations
     *
     * This class defines a collection of auxiliary functions and algorithms for
     * performing various geometric computations, making it a valuable resource for
     * geometric operations
     *
     * @tparam typeT The type of coordinates used in the Point
     * @tparam nDim The dimension in which the points exist
     */
    template<typename typeT, std::size_t nDim>
    class Utils
    {
        public:
            /**
             * @brief Given two points, calculates the distance between them
             * @param a, b Points to be used in the distance calculation
             * @return Double representing the distance between the two points
             */
            static double_t Distance(Point<typeT, nDim> a, Point<typeT, nDim> b);

            /**
             * @brief Computes the polar angle of point 'a'
             * @param ref Reference point for polar angle calculation
             * @param a Point to be used in the angle calculation
             * @return Double with the angle value in radians
             */
            static double_t PolarAngle(Point<typeT, nDim> ref, Point<typeT, nDim> a);

            /**
             * @brief Creates a pseudo-random set of points in the plane
             * @param amount Number of points to be generated
             * @param min, max Minimum and maximum values for the X, Y coordinates
             *        of the points
             * @param points Vector where the generated points will be stored
             */
            static void CreateRandomPoints(std::size_t amount, typeT min, typeT max,
                                           Vector<Point<typeT, nDim>>& points);

            /**
             * @brief Determines whether the vector ref->b is in a clockwise
             * direction relative to the vector ref->a
             * @param ref, a, b Points used in the calculation
             * @return CLOCKWISE, ANTICLOCKWISE, or COLLINEAR
             */
            static PointOrientation Clockwise(Point<typeT, nDim>& ref,
                                              Point<typeT, nDim>& a,
                                              Point<typeT, nDim>& b);

            /**
             * @brief Determines if a set of points forms a valid polygon
             * @param points Vector of points to be evaluated
             * @return True if the set forms a valid polygon, False otherwise
             */
            static bool IsPolygon(Vector<Point<typeT, nDim>>& points);
    };

    template<typename typeT, std::size_t nDim>
    double_t Utils<typeT, nDim>::Distance(Point<typeT, nDim> a, Point<typeT, nDim> b)
    {
        double_t distanceSquared = 0;

        // Calculate the distance between two points in n-dimensional space
        for (std::size_t i = 0; i < nDim; i++)
        {
            typeT diff = b.GetCoordinates().At(i) - a.GetCoordinates().At(i);
            distanceSquared += static_cast<double_t>(diff) * static_cast<double_t>(diff);
        }

        return std::sqrt(distanceSquared);
    }

    template<typename typeT, std::size_t nDim>
    double_t Utils<typeT, nDim>::PolarAngle(Point<typeT, nDim> ref, Point<typeT, nDim> a)
    {
        // NOTE: Perhaps the calculation of the polar angle below may be invalid for nDim
        // >= 3
        if (nDim != 2)
            throw std::runtime_error(
                "Polar angle function only supports nDim equal to 2");

        if (ref == a)
            return 0;

        // Considering 2-dimensional, where 0 == x and 1 == y (index in the vector)
        uint8_t xCoordinate = 0;
        uint8_t yCoordinate = 1;
        double_t angle = std::atan2(
            a.GetCoordinates().At(yCoordinate) - ref.GetCoordinates().At(yCoordinate),
            a.GetCoordinates().At(xCoordinate) - ref.GetCoordinates().At(xCoordinate));

        if (angle < 0)
            angle += 2 * PI;

        return angle;
    }

    template<typename typeT, std::size_t nDim>
    void Utils<typeT, nDim>::CreateRandomPoints(std::size_t amount, typeT min, typeT max,
                                                Vector<Point<typeT, nDim>>& points)
    {
        std::srand(time(nullptr));

        points.Clear();

        for (std::size_t i = 0; i < amount; i++)
        {
            Vector<typeT> coordinates;

            for (std::size_t j = 0; j < nDim; j++)
            {
                coordinates.PushBack(GEN_NUM);
            }

            points.PushBack(Point<typeT, nDim>(coordinates));
        }
    }

    template<typename typeT, std::size_t nDim>
    PointOrientation Utils<typeT, nDim>::Clockwise(Point<typeT, nDim>& ref,
                                                   Point<typeT, nDim>& a,
                                                   Point<typeT, nDim>& b)
    {
        if (nDim != 2)
        {
            throw std::runtime_error("Clockwise function only supports nDim equal to 2");
        }

        // Considering 2-dimensional, where 0 == x and 1 == y (index in the vector)
        uint8_t xCoordinate = 0;
        uint8_t yCoordinate = 1;
        double_t determinant =
            (a.GetCoordinates().At(xCoordinate) - ref.GetCoordinates().At(xCoordinate)) *
                (b.GetCoordinates().At(yCoordinate) -
                 ref.GetCoordinates().At(yCoordinate)) -
            (a.GetCoordinates().At(yCoordinate) - ref.GetCoordinates().At(yCoordinate)) *
                (b.GetCoordinates().At(xCoordinate) -
                 ref.GetCoordinates().At(xCoordinate));

        if (determinant > 0)
            return PointOrientation::ANTICLOCKWISE;

        else if (determinant < 0)
            return PointOrientation::CLOCKWISE;

        else
            return PointOrientation::COLLINEAR;
    }

    template<typename typeT, std::size_t nDim>
    bool Utils<typeT, nDim>::IsPolygon(Vector<Point<typeT, nDim>>& points)
    {
        if (points.Size() < 3)
            return false;

        for (std::size_t i = 0; i < points.Size() - 2; i++)
        {
            if (Utils<typeT, nDim>::Clockwise(points[i], points[i + 1], points[i + 2]) !=
                COLLINEAR)
                return true;
        }

        return false;
    }
} // namespace geom
