#pragma once

#include <functional>

namespace lgm {

    struct Point {
        double x;
        double y;

        explicit Point(double _x = 0, double _y = 0);
    };

    enum class Direction {
        CCW, COLLINEAR, CW
    };

    /*
    * CCW returns direction of of the p relatively to segment pq
    */
    Direction ccw(const Point &p, const Point &q, const Point &r);

    double distance(const Point &lhs, const Point &rhs);

    double dot(const Point &, const Point &);
    double cross(const Point &, const Point &);

    Point operator*(const double, const Point &);
    Point operator*(const Point&, const double);
    Point operator/(const Point&, const double);
    Point operator+(const Point &, const Point &);
    Point operator-(const Point &, const Point &);

    bool operator==(const Point &, const Point &);
    bool operator!=(const Point &, const Point &);
    bool operator< (const Point &, const Point &);
    bool operator<=(const Point &, const Point &);
    bool operator> (const Point &, const Point &);
    bool operator>=(const Point &, const Point &);

    /*
     * CCW returns 1 if r is on the right side of the pq
     *             0 if r is collinear with pq
     *             -1 if r is on the left side of the pq
     */
}

namespace std {
    template<>
    struct hash<lgm::Point> {
        std::size_t operator()(const lgm::Point& point) const {
            return point.x + 31 * point.y;
        }
    };
}