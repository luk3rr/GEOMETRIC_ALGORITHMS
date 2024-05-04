/*
 * Filename: convex_hull_test.cc
 * Created on: June  8, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include "convex_hull.h"
#include "point.h"
#include "vector.h"
#include <cstddef>

void GeneratePoints(Vector<geom::Point<int, 2>>& points,
                    Vector<geom::Point<int, 2>>& checker,
                    bool                         colinear = false)
{
    geom::Point<int, 2> a({ 6, 2 });
    geom::Point<int, 2> b({ 16, 0 });
    geom::Point<int, 2> c({ 24, 6 });
    geom::Point<int, 2> d({ 16, 10 });
    geom::Point<int, 2> e({ 24, 12 });
    geom::Point<int, 2> f({ 12, 8 });
    geom::Point<int, 2> g({ 10, 0 });
    geom::Point<int, 2> h({ 17, 6 });
    geom::Point<int, 2> i({ 8, 1 });
    geom::Point<int, 2> j({ 10, 10 });
    geom::Point<int, 2> k({ 10, 8 });
    geom::Point<int, 2> l({ 10, 6 });
    geom::Point<int, 2> m({ 10, 4 });
    geom::Point<int, 2> n({ 14, 0 });

    points.PushBack(a);
    points.PushBack(b);
    points.PushBack(c);
    points.PushBack(d);
    points.PushBack(e);
    points.PushBack(f);
    points.PushBack(g);
    points.PushBack(h);
    points.PushBack(i);
    points.PushBack(j);
    points.PushBack(k);
    points.PushBack(l);
    points.PushBack(m);
    points.PushBack(n);

    if (colinear)
    {
        checker.PushBack(g);
        checker.PushBack(n);
        checker.PushBack(b);
        checker.PushBack(c);
        checker.PushBack(e);
        checker.PushBack(j);
        checker.PushBack(a);
        checker.PushBack(i);
        checker.PushBack(g);
    }
    else
    {
        checker.PushBack(g);
        checker.PushBack(b);
        checker.PushBack(c);
        checker.PushBack(e);
        checker.PushBack(j);
        checker.PushBack(a);
        checker.PushBack(g);
    }
}

void RunGrahamScan(Vector<geom::Point<int, 2>>& points,
                   Vector<geom::Point<int, 2>>& checker,
                   Vector<geom::Point<int, 2>>& convex,
                   geom::SelectSortAlgorithm    sortType)
{
    geom::ConvexHull<int, 2>::GrahamScan(points, convex, sortType);

    bool pass = checker == convex;

    CHECK(pass);

    if (not pass)
    {
        std::cout << " GRAHAM WITH SORT TYPE " << sortType << std::endl;
        for (unsigned int i = 0;
             i < unsigned(comparators::Max<std::size_t>(convex.Size(), checker.Size()));
             i++)
        {
            if (i < convex.Size())
            {
                std::cout << convex[i];
            }
            if (i < checker.Size())
            {
                std::cout << " ~ " << checker[i];
            }
            std::cout << std::endl;
        }
    }
}

TEST_CASE("Fecho convexo: Graham Scan")
{
    // Considera pontos colineares
    Vector<geom::Point<int, 2>> points;
    Vector<geom::Point<int, 2>> checker;
    Vector<geom::Point<int, 2>> convex;

    SUBCASE("BubbleSort")
    {
        GeneratePoints(points, checker, true);
        RunGrahamScan(points, checker, convex, geom::SelectSortAlgorithm::BUBBLE_SORT);
    }

    SUBCASE("BucketSort")
    {
        GeneratePoints(points, checker, true);
        RunGrahamScan(points, checker, convex, geom::SelectSortAlgorithm::BUCKET_SORT);
    }

    SUBCASE("HeapSort")
    {
        GeneratePoints(points, checker, true);
        RunGrahamScan(points, checker, convex, geom::SelectSortAlgorithm::HEAP_SORT);
    }

    SUBCASE("InsertionSort")
    {
        GeneratePoints(points, checker, true);
        RunGrahamScan(points,
                      checker,
                      convex,
                      geom::SelectSortAlgorithm::INSERTION_SORT);
    }

    SUBCASE("MergeSort")
    {
        GeneratePoints(points, checker, true);
        RunGrahamScan(points, checker, convex, geom::SelectSortAlgorithm::MERGE_SORT);
    }

    SUBCASE("QuickSort")
    {
        GeneratePoints(points, checker, true);
        RunGrahamScan(points, checker, convex, geom::SelectSortAlgorithm::QUICK_SORT);
    }

    SUBCASE("SelectionSort")
    {
        GeneratePoints(points, checker, true);
        RunGrahamScan(points,
                      checker,
                      convex,
                      geom::SelectSortAlgorithm::SELECTION_SORT);
    }

    SUBCASE("ShellSort")
    {
        GeneratePoints(points, checker, true);
        RunGrahamScan(points, checker, convex, geom::SelectSortAlgorithm::SHELL_SORT);
    }
}

TEST_CASE("Fecho convexo: Jarvis March")
{
    // Não considera pontos colineares
    Vector<geom::Point<int, 2>> points;
    Vector<geom::Point<int, 2>> checker;
    Vector<geom::Point<int, 2>> convex;

    GeneratePoints(points, checker);

    geom::ConvexHull<int, 2>::JarvisMarch(points, convex);

    bool pass = checker == convex;

    CHECK(pass);

    if (not pass)
    {
        std::cout << " JARVIS "
                  << " CHECKER " << std::endl;
        for (unsigned int i = 0;
             i < unsigned(comparators::Max<std::size_t>(convex.Size(), checker.Size()));
             i++)
        {
            if (i < convex.Size())
            {
                std::cout << convex[i];
            }
            if (i < checker.Size())
            {
                std::cout << " ~ " << checker[i];
            }
            std::cout << std::endl;
        }
    }
}

TEST_CASE("Encontrar o ponto mais 'baixo'")
{
    Vector<geom::Point<int, 2>> points;

    geom::Point<int, 2> a({ 6, 2 });
    geom::Point<int, 2> b({ 16, 0 });
    geom::Point<int, 2> c({ 24, 6 });
    geom::Point<int, 2> d({ 16, 10 });
    geom::Point<int, 2> e({ 24, 12 });
    geom::Point<int, 2> f({ 12, 8 });
    geom::Point<int, 2> g({ 10, 0 });

    points.PushBack(a);
    points.PushBack(b);
    points.PushBack(c);
    points.PushBack(d);
    points.PushBack(e);
    points.PushBack(f);
    points.PushBack(g);

    CHECK(points[geom::ConvexHull<int, 2>::FindLowestPoint(points)] == g);
}
