//
// Created by dmitr on 4/20/2020.
//

#include <tuple>
#include <algorithm>
#include <stdexcept>
#include "../headers/Segment.h"

namespace lgm {
    Segment::Segment(Point start, Point end) : start_(start), end_(end) {}
    RefSegment::RefSegment(Point &start, Point &end) : start_(start), end_(end) {}

    double AbstractSegment::length() const {
        return distance(start(), end());
    }

    bool intersects(const AbstractSegment &lhs, const AbstractSegment &rhs) {
        Direction o1 = ccw(lhs.start(), lhs.end(), rhs.start());
        Direction o2 = ccw(lhs.start(), lhs.end(), rhs.end());
        Direction o3 = ccw(rhs.start(), rhs.end(), rhs.start());
        Direction o4 = ccw(rhs.start(), rhs.end(), rhs.end());

        if (o1 == Direction::COLLINEAR && onSegment(lhs, rhs.start())) return true;
        if (o2 == Direction::COLLINEAR && onSegment(lhs, rhs.end()))   return true;
        if (o3 == Direction::COLLINEAR && onSegment(rhs, lhs.start())) return true;
        if (o4 == Direction::COLLINEAR && onSegment(rhs, lhs.end()))   return true;

        return o1 != o2 && o3 != o4;
    }

    Point calculateIntersection(const Segment &lhs, const Segment &rhs) {
        Point r = lhs.end() - lhs.start();
        Point s = rhs.end() - rhs.start();

        if (cross(r, s) == 0 && cross((rhs.start() - lhs.start()),r) == 0) {
            double t0 = dot((rhs.start() - lhs.start()), r) / dot(r, r);
            double t1 = t0 + dot(s, r) / dot(r, r);

            if (t1 < t0)
                std::swap(t0, t1);

            if (t1 == 0)
                return lhs.start();
            if (t0 == 1)
                return lhs.end();
            throw std::logic_error("Segments do not intersect! Consider using intersects() before using this function.");
        }
        else if (cross(r, s) == 0 && cross(rhs.start() - lhs.start(), r) != 0)
            throw std::logic_error("Segments do not intersect! Consider using intersects() before using this function.");
        else {
            double t = cross((rhs.start() - lhs.start()), s) / cross(r, s);
            double u = cross((rhs.start() - lhs.start()), r) / cross(r, s);

            if (t < 0 || t > 1 || u < 0 || u > 1)
                throw std::logic_error("Segments do not intersect! Consider using intersects() before using this function.");
            return lhs.start() + t * r;
        }
    }

    bool onSegment(const AbstractSegment &pq, const Point &r)
    {
        return r.x <= std::max(pq.start().x, pq.end().x) && r.x >= std::min(pq.start().x, pq.end().x) &&
               r.y <= std::max(pq.start().y, pq.end().y) && r.y >= std::min(pq.start().y, pq.end().y);
    }

    Direction ccw(const AbstractSegment& pq, const Point &r) {
        return ccw(pq.start(), pq.end(), r);
    }

    bool operator==(const AbstractSegment &lhs, const AbstractSegment &rhs) {
        return lhs.start() == rhs.start() && lhs.end() == rhs.end();
    }
    bool operator!=(const AbstractSegment &lhs, const AbstractSegment &rhs) {
        return !(lhs == rhs);
    }
    bool operator<(const AbstractSegment &lhs, const AbstractSegment &rhs) {
        return std::tie(lhs.start(), lhs.end()) < std::tie(rhs.start(), rhs.end());
    }
    bool operator<=(const AbstractSegment &lhs, const AbstractSegment &rhs) {
        return std::tie(lhs.start(), lhs.end()) <= std::tie(rhs.start(), rhs.end());
    }
    bool operator>(const AbstractSegment &lhs, const AbstractSegment &rhs) {
        return std::tie(lhs.start(), lhs.end()) > std::tie(rhs.start(), rhs.end());
    }
    bool operator>=(const AbstractSegment &lhs, const AbstractSegment &rhs) {
        return std::tie(lhs.start(), lhs.end()) >= std::tie(rhs.start(), rhs.end());
    }

    Point &RefSegment::start() {
        return start_;
    }

    Point &RefSegment::end() {
        return end_;
    }

    const Point &RefSegment::start() const {
        return start_;
    }

    const Point &RefSegment::end() const {
        return end_;
    }

    Point &Segment::start() {
        return start_;
    }

    Point &Segment::end() {
        return end_;
    }

    const Point &Segment::start() const {
        return start_;
    }

    const Point &Segment::end() const {
        return end_;
    }
}