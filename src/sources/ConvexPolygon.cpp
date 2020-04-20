//
// Created by dmitr on 4/20/2020.
//

#include <stdexcept>
#include <cmath>
#include <deque>
#include <algorithm>

#include "../headers/ConvexPolygon.h"

lgm::ConvexPolygon::ConvexPolygon(std::vector<Point> vertices) : Polygon(std::move(vertices)) {
    if (!isConvex(vertices_))
        throw std::logic_error("ConvexPolygon is not convex.");
    calculateWedges();
}

lgm::ConvexPolygon::ConvexPolygon(const std::vector<Segment> &edges) : Polygon(edges ){
    if (!isConvex(vertices_))
        throw std::logic_error("ConvexPolygon is not convex.");
    calculateWedges();
}

void lgm::ConvexPolygon::calculateWedges() {
    wedges_.clear();
    Point z = calculateInsidePoint(vertices_);
    for (size_t i = 0; i < size(); ++i) {
        wedges_.emplace_back(std::atan2(vertices_[i].y - z.y, vertices_[i].x - z.x) + 3.1415926);
    }
}

bool lgm::ConvexPolygon::contains(const lgm::Point &p) const {
    Point z = calculateInsidePoint(vertices());
    double angle = std::atan2(p.y - z.y, p.x - z.x) + 3.1415926;

    int l = -1;
    int r = wedges_.size() - 1;
    while (l < r) {
        size_t m = (l + r) / 2;
        if (wedges_[m] >= angle)
            r = m;
        else
            l = m + 1;
    }
    Point vertex = vertices_[r];
    Point prev = vertices_[(r - 1 + size()) % size()];

    Direction p_sgn = ccw(vertex, prev, p);
    Direction z_sgn = ccw(vertex, prev, z);
    if (p_sgn == Direction::COLLINEAR) return true; //border
    return !(p_sgn != z_sgn);

}

bool lgm::ConvexPolygon::isBoundary(const lgm::Point &p) const {
    Point z = calculateInsidePoint(vertices());
    double angle = std::atan2(p.y - z.y, p.x - z.x) + 3.1415926;

    int l = -1;
    int r = wedges_.size() - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (wedges_[m] >= angle)
            r = m;
        else
            l = m + 1;
    }
    Point vertex = vertices_[r];
    Point prev = vertices_[(r - 1 + size()) % size()];

    Direction p_sgn = ccw(vertex, prev, p);
    return p_sgn == Direction::COLLINEAR;
}

void lgm::ConvexPolygon::add(const lgm::Point &point) {
    Polygon::add(point);
    if (!isConvex(vertices()))
        throw std::logic_error("Newly added point ruined convexity of polygon.");
}

lgm::ConvexPolygon lgm::ModifiedGrahamScan(const std::vector<lgm::Point>& origin) {
    std::vector<Point> points = origin;
    std::stable_sort(points.begin(), points.end());

    std::deque<Point> answer;
    answer.push_back(points.at(0));
    answer.push_back(points.at(1));
    for (unsigned int i = 2; i < points.size(); ++i) {
        while (answer.size() > 1 && ccw(answer.at(answer.size() - 2), answer.back(), points[i]) != Direction::CCW) {
            answer.pop_back();
        }
        answer.push_back(points[i]);
    }
    int start = points.size() - 2;
    while (answer.size() > 1 && ccw(answer.at(answer.size() - 2), answer.back(), points[start]) == Direction::COLLINEAR) {
        start--;
    }
    for (int i = start; i >= 0; --i) {
        while (answer.size() > 1 && ccw(answer.at(answer.size() - 2), answer.back(), points[i]) != Direction::CCW) {
            answer.pop_back();
        }
        answer.push_back(points[i]);
    }
    answer.pop_back();
    std::vector<Point> v_answer(answer.begin(), answer.end());
    while (ccw(v_answer.at(v_answer.size() - 1), v_answer.at(0), v_answer.at(1)) == Direction::COLLINEAR)
        v_answer.pop_back();
    return ConvexPolygon(v_answer);
}