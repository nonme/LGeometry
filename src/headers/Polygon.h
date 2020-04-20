#pragma once

#include <vector>
#include "Point.h"
#include "Segment.h"

namespace lgm {
    class Polygon {
    public:
        explicit Polygon(std::vector<Point>);
        explicit Polygon(const std::vector<Segment>&);

        double area() const;
        double perimeter() const;

        virtual bool contains(const Point&) const;
        virtual bool isBoundary(const Point&) const;

        virtual void add(const Point&);

        const std::vector<Point>& vertices() const;
        const std::vector<RefSegment>& edges() const;
        size_t size() const;
    protected:
        std::vector<Point> vertices_;
        std::vector<RefSegment> edges_;
        bool isClockwise;
    };

    bool isConvex(const std::vector<lgm::Point> &);
    Point calculateInsidePoint(const std::vector<Point>&);
}