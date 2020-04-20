//
// Created by dmitr on 4/20/2020.
//

#include <tuple>

#include "../headers/Point.h"

namespace lgm {
    Point::Point(double _x, double _y) : x(_x), y(_y) {}

    Direction ccw(const Point &p, const Point &q, const Point &r) {
        int det = static_cast<int>((q.x - p.x) * (r.y - p.y) - (r.x - p.x) * (q.y - p.y));
        return (det > 0 ? Direction::CCW : (det < 0 ? Direction::CW : Direction::COLLINEAR));
    }

    double distance(const Point &lhs, const Point &rhs) {
        double dx = rhs.x - lhs.x;
        double dy = rhs.y - lhs.y;
        return sqrt(dx * dx + dy * dy);
    }

    double dot(const Point &lhs, const Point &rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
    double cross(const Point &lhs, const Point &rhs) {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

    Point operator*(const double lhs, const Point &rhs) {
        return Point(lhs * rhs.x, lhs * rhs.y);
    }
    Point operator*(const Point &lhs, const double rhs) {
        return rhs * lhs;
    }
    Point operator/(const Point &lhs, const double rhs) {
        return Point(lhs.x / rhs, lhs.y / rhs);
    }
    Point operator+(const Point &lhs, const Point &rhs) {
        return Point(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    Point operator-(const Point &lhs, const Point &rhs) {
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    bool operator==(const Point &lhs, const Point &rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    bool operator!=(const Point &lhs, const Point &rhs) {
        return !(lhs == rhs);
    }
    bool operator<(const Point &lhs, const Point &rhs) {
        return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
    }
    bool operator<=(const Point &lhs, const Point &rhs) {
        return !(lhs > rhs);
    }
    bool operator>(const Point &lhs, const Point &rhs) {
        return rhs < lhs;
    }
    bool operator>=(const Point &lhs, const Point &rhs) {
        return !(lhs < rhs);
    }
}

