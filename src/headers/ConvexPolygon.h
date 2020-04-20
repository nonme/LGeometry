#pragma once

#include "Polygon.h"

namespace lgm {
    class ConvexPolygon : public Polygon {
    public:
        explicit ConvexPolygon(std::vector<Point>);
        explicit ConvexPolygon(const std::vector<Segment>&);

        bool contains(const Point &point) const override;
        bool isBoundary(const Point &point) const override;

        void add(const Point &point) override;
    private:
        /*
         * While Polygon determines vertex position in O(N), ConvexPolygon can do this in O(logN) using binary search
         * with O(N) pre-processing step
         */
        void calculateWedges();
        std::vector<double> wedges_;
    };
    ConvexPolygon ModifiedGrahamScan(const std::vector<Point>& origin);
}