/*
 * Filename: convex_hull.h
 * Created on: June  7, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef CONVEX_HULL_H_
#define CONVEX_HULL_H_

#include <cstddef>
#include <cstdint>

#include "bubble_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"
#include "shell_sort.h"
#include "vector.h"

#include "geometry_utils.h"
#include "point.h"

namespace geom
{
    enum SelectSortAlgorithm
    {
        BUBBLE_SORT,
        BUCKET_SORT,
        HEAP_SORT,
        INSERTION_SORT,
        MERGE_SORT,
        QUICK_SORT,
        SELECTION_SORT,
        SHELL_SORT
    };

    /**
     * @brief A class for computing the Convex Hull of a set of points in n-dimensional
     * space.
     *
     * This class contains a collection of algorithms for finding the convex hull,
     * offering various methods to compute it in different scenarios
     *
     * @tparam typeT The type of coordinates used in the Point
     * @tparam nDim The dimension in which the points exist
     *
     * NOTE: The convex hull algorithms implemented here only work for nDim = 2
     */
    template<typename typeT, std::size_t nDim = 2>
    class ConvexHull
    {
        public:
            /**
             * @brief Uses the Graham Scan algorithm to find the convex hull of a set of
             *        points
             * @param points Set of points for which the convex hull will be found
             * @param convex Ordered set of points that form the convex hull
             * @param sort The sorting algorithm to use for the Graham Scan (default is
             * Heap Sort)
             */
            static void
            GrahamScan(Vector<Point<typeT, nDim>>& points,
                       Vector<Point<typeT, nDim>>& convex,
                       SelectSortAlgorithm sort = SelectSortAlgorithm::HEAP_SORT);

            /**
             * @brief Uses the Jarvis March algorithm to find the convex hull of a set
             *        of points
             * @param points Set of points for which the convex hull will be found
             * @param convex Ordered set of points that form the convex hull
             */
            static void JarvisMarch(Vector<Point<typeT, nDim>>& points,
                                    Vector<Point<typeT, nDim>>& convex);

            /**
             * @brief Checks if the polar angle of point 'a' is smaller than the polar
             *        angle of point 'b'
             *        For collinear points, it takes into account the shorter distance
             *        when the angle is less than or equal to 90°
             *
             * @param ref Reference point for polar angle and distance calculations
             * @param a, b Points to be compared
             * @return True if the polar angle of 'a' is smaller than that of 'b', False
             * otherwise
             */
            static bool ComparePoints(const Point<typeT, nDim>& ref,
                                      const Point<typeT, nDim>& a,
                                      const Point<typeT, nDim>& b);

            /**
             * @brief Given a set of points, finds the one with the lowest Y-coordinate.
             *        In case of a tie, the point with the lowest X-coordinate will be
             * chosen.
             * @param points Set of points in which the search will be performed
             * @return The index of the lowest point
             */
            static std::size_t FindLowestPoint(Vector<Point<typeT, nDim>>& points);

            /**
             * @brief Custom comparator for ordering points
             */
            struct ComparePointsByPolarAngle
            {
                    // Referece point used in the polar angle calculus
                    Point<typeT, nDim> m_refPoint;

                    ComparePointsByPolarAngle(Point<typeT, nDim>& refPoint)
                        : m_refPoint(refPoint)
                    { }

                    bool operator()(const Point<typeT, nDim>& p1,
                                    const Point<typeT, nDim>& p2) const
                    {
                        return ComparePoints(m_refPoint, p1, p2);
                    }
            };
    };

    template<typename typeT, std::size_t nDim>
    void ConvexHull<typeT, nDim>::GrahamScan(Vector<Point<typeT, nDim>>& points,
                                             Vector<Point<typeT, nDim>>& convex,
                                             SelectSortAlgorithm         sort)
    {
        std::size_t lowestPointIndex = FindLowestPoint(points);

        switch (sort)
        {
            case SelectSortAlgorithm::BUBBLE_SORT:
                sort::Bubble(points,
                             (ComparePointsByPolarAngle(points[lowestPointIndex])));
                break;

            case SelectSortAlgorithm::INSERTION_SORT:
                sort::Insertion(points,
                                (ComparePointsByPolarAngle(points[lowestPointIndex])));
                break;

            case SelectSortAlgorithm::MERGE_SORT:
                sort::Merge(points,
                            (ComparePointsByPolarAngle(points[lowestPointIndex])));
                break;

            case SelectSortAlgorithm::QUICK_SORT:
                sort::Quick(points,
                            (ComparePointsByPolarAngle(points[lowestPointIndex])));
                break;

            case SelectSortAlgorithm::SELECTION_SORT:
                sort::Selection(points,
                                (ComparePointsByPolarAngle(points[lowestPointIndex])));
                break;

            case SelectSortAlgorithm::SHELL_SORT:
                sort::Shell(points,
                            (ComparePointsByPolarAngle(points[lowestPointIndex])));
                break;

            case SelectSortAlgorithm::BUCKET_SORT:
            case SelectSortAlgorithm::HEAP_SORT:
                std::cout
                    << "WARNING: The selected sorting algorithm is not suitable for "
                       "Graham Scan. Using Quick Sort instead"
                    << std::endl;
                sort::Quick(points,
                            (ComparePointsByPolarAngle(points[lowestPointIndex])));
                break;
        }

        convex.Clear();

        int8_t clockwise;

        convex.PushBack(points[0]);
        convex.PushBack(points[1]);

        for (std::size_t i = 2; i < points.Size(); i++)
        {
            while (convex.Size() > 2)
            {
                clockwise = Utils<typeT, nDim>::Clockwise(convex[convex.Size() - 2],
                                                          convex[convex.Size() - 1],
                                                          points[i]);

                if (clockwise != PointOrientation::ANTICLOCKWISE)
                {
                    convex.PopBack();
                    continue;
                }
                break;
            }
            convex.PushBack(points[i]);
        }
        convex.PushBack(points[0]);
    }

    template<typename typeT, std::size_t nDim>
    void ConvexHull<typeT, nDim>::JarvisMarch(Vector<Point<typeT, nDim>>& points,
                                              Vector<Point<typeT, nDim>>& convex)
    {
        convex.Clear();

        std::size_t lowestPointIndex = FindLowestPoint(points);

        Point<typeT, nDim> lowestPoint = points[lowestPointIndex];

        int8_t clockwise;

        std::size_t currentPointIndex = lowestPointIndex;
        std::size_t nextPointIndex;

        do
        {
            convex.PushBack(points[currentPointIndex]);

            nextPointIndex = (currentPointIndex + 1) % points.Size();

            for (std::size_t i = 0; i < points.Size(); i++)
            {
                clockwise = Utils<typeT, nDim>::Clockwise(points[currentPointIndex],
                                                          points[i],
                                                          points[nextPointIndex]);

                if (clockwise == PointOrientation::ANTICLOCKWISE)
                {
                    nextPointIndex = i;
                }
            }
            currentPointIndex = nextPointIndex;

        } while (currentPointIndex != lowestPointIndex);

        convex.PushBack(lowestPoint);
    }

    template<typename typeT, std::size_t nDim>
    bool ConvexHull<typeT, nDim>::ComparePoints(const Point<typeT, nDim>& ref,
                                                const Point<typeT, nDim>& a,
                                                const Point<typeT, nDim>& b)
    {
        double_t polarAngleA = Utils<typeT, nDim>::PolarAngle(ref, a);
        double_t polarAngleB = Utils<typeT, nDim>::PolarAngle(ref, b);

        if (polarAngleA < polarAngleB)
        {
            return true;
        }
        else if (polarAngleA == polarAngleB)
        {
            if (polarAngleA <= PI / 2)
                return Utils<typeT, nDim>::Distance(ref, a) <
                       Utils<typeT, nDim>::Distance(ref, b);

            else
                return Utils<typeT, nDim>::Distance(ref, a) >
                       Utils<typeT, nDim>::Distance(ref, b);
        }

        return false;
    }

    template<typename typeT, std::size_t nDim>
    std::size_t
    ConvexHull<typeT, nDim>::FindLowestPoint(Vector<Point<typeT, nDim>>& points)
    {
        std::size_t lowest = 0;

        // Since the convex hull works only for nDim = 2, we consider the x-coordinate
        // as the first element of the vector and the y-coordinate as the second
        uint8_t xCoordinate = 0;
        uint8_t yCoordinate = 1;

        // For the purposes of convex hull algorithms, the 'lowest' point is the one
        // with the smallest Y-coordinate. In case of a tie, the 'lowest' point will be
        // the one with the smallest X-coordinate
        for (std::size_t i = 1; i < points.Size(); i++)
        {
            if (points[i].GetCoordinates().At(yCoordinate) <
                points[lowest].GetCoordinates().At(yCoordinate))
                lowest = i;

            if (points[i].GetCoordinates().At(yCoordinate) ==
                points[lowest].GetCoordinates().At(yCoordinate))
            {
                if (points[i].GetCoordinates().At(xCoordinate) <
                    points[lowest].GetCoordinates().At(xCoordinate))
                {
                    lowest = i;
                }
            }
        }

        return lowest;
    }
} // namespace geom

#endif // CONVEX_HULL_H_
