#pragma once

#include <functional>
#include "Point.h"

namespace lgm {
    class AbstractSegment {
    public:
        double length() const;

        virtual Point& start() = 0;
        virtual Point& end() = 0;

        virtual const Point& start() const = 0;
        virtual const Point& end() const = 0;
    };

    struct Segment : public AbstractSegment {
    public:
        Point &start() override;
        Point &end() override;
        const Point &start() const override;
        const Point &end() const override;

        explicit Segment(Point _start = Point(), Point _end = Point());
    private:
        Point start_;
        Point end_;
    };

    struct RefSegment : public AbstractSegment {
    public:
        RefSegment(Point& start, Point& end);

        Point &start() override;
        Point &end() override;
        const Point &start() const override;
        const Point &end() const override;

    private:
        Point& start_;
        Point& end_;
    };


    bool intersects(const AbstractSegment&, const AbstractSegment&);
    Point calculateIntersection(const Segment&, const Segment&);
    bool onSegment(const AbstractSegment&, const Point& r);

    Direction ccw(const AbstractSegment& pq, const Point &r);

    bool operator==(const AbstractSegment &, const AbstractSegment &);
    bool operator!=(const AbstractSegment &, const AbstractSegment &);
    bool operator< (const AbstractSegment &, const AbstractSegment &);
    bool operator<=(const AbstractSegment &, const AbstractSegment &);
    bool operator> (const AbstractSegment &, const AbstractSegment &);
    bool operator>=(const AbstractSegment &, const AbstractSegment &);
}

namespace std {
    template<>
    struct hash<lgm::AbstractSegment> {
        std::size_t operator()(const lgm::AbstractSegment &segment) const {
            return std::hash<lgm::Point>()(segment.start()) ^ (std::hash<lgm::Point>()(segment.end()) << 1);
        }
    };
}