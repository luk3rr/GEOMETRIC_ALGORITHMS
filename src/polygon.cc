/*
* Filename: polygon.cc
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "polygon.h"

namespace geom {
    Polygon::Polygon() { }

    Polygon::Polygon(dlkd::List<Point2D> points) {
        this->m_points = points;
    }

    int Polygon::GetNumPoints() {
        return m_points.Size();
    }

    void Polygon::InsertPoint(Point2D point) {
        this->m_points.PushBack(point);
    }

    void Polygon::InsertPoint(int x, int y) {
        this->m_points.PushBack(Point2D(x, y));
    }

    void Polygon::DeletePoint(Point2D point) {
        this->m_points.Remove(point);
    }

    void Polygon::DeletePoint(int x, int y) {
        this->m_points.Remove(Point2D(x, y));
    }

    void Polygon::Delete() {
        this->m_points.Clear();
    }

    bool Polygon::IsPointOnPolygon(Point2D point) {
        if (this->m_points.Search(point))
            return true;
        else
            return false;
    }

    bool Polygon::IsPointOnPolygon(int x, int y) {
        if (this->m_points.Search(Point2D(x, y)))
            return true;
        else
            return false;
    }
}
