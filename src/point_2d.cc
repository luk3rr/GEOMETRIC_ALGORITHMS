/*
* Filename: point_2d.cc
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "point_2d.h"

namespace geom {
    Point2D::Point2D() {
        this->m_x = 0;
        this->m_y = 0;
    }

    Point2D::Point2D(int x, int y) {
        this->m_x = x;
        this->m_y = y;
    }

    bool Point2D::operator==(const Point2D &point) const {
        return (this->m_x == point.m_x and this->m_y == point.m_y);
    }

    bool Point2D::operator<(const Point2D &point) const {
        if (this->m_y < point.m_y)
            return true;
        if (this->m_y == point.m_y) {
            if (this->m_x < point.m_x) {
                return true;
            }
        }

        return false;
    }

    void Point2D::SetX(int x) {
        this->m_x = x;
    }

    void Point2D::SetY(int y) {
        this->m_y = y;
    }

    int Point2D::GetX() {
        return this->m_x;
    }

    int Point2D::GetY() {
        return this->m_y;
    }
}
