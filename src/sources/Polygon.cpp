//
// Created by dmitr on 4/20/2020.
//

#include <stdexcept>
#include <string>
#include <algorithm>
#include "../headers/Polygon.h"

lgm::Polygon::Polygon(std::vector<Point> vertices) : vertices_(std::move(vertices)) {
    if (vertices_.size() < 3)
        throw std::logic_error("Polygon must have 3 or more vertices. "
                               "Number of vertices provided: " + std::to_string(vertices.size()));
    for (size_t i = 0; i < vertices_.size(); ++i) {
        edges_.emplace_back(vertices_[i], vertices_[(i + 1) % vertices_.size()]);

        if (ccw(edges_[i], vertices_[(i + 2) % vertices_.size()]) == Direction::COLLINEAR) {
            throw std::invalid_argument("Three consecutive collinear points are not supported yet.");
        }
    }
    isClockwise = ccw(edges_.front(), vertices_[2]) == Direction::CW;
}

lgm::Polygon::Polygon(const std::vector<Segment>& edges) {
    if (edges_.size() <= 2)
        throw std::logic_error("Polygon must have 3 or more edges. "
                               "Number of edges provided: " + std::to_string(edges.size()));
    if (edges_.front().start() != edges_.back().end())
        throw std::invalid_argument("Start vertex of the first edge must be the end vertex of the last edge.");

    vertices_.reserve(edges_.size());
    for (size_t i = 0; i < vertices_.size(); ++i) {
        vertices_[i] = edges[i].start();
    }
    for (size_t i = 0; i < vertices_.size(); ++i) {
        edges_.emplace_back(vertices_[i], vertices_[(i + 1) % vertices_.size()]);

        if (ccw(edges_[i], vertices_[(i + 2) % vertices_.size()]) == Direction::COLLINEAR) {
            throw std::invalid_argument("Three consecutive collinear points are not supported yet.");
        }
    }
    if (ccw(edges_.front(), vertices_[2]) == Direction::CW)
        isClockwise = true;
}

double lgm::Polygon::area() const {
    double area = 0;
    for (const auto &edge : edges_) {
        area += cross(edge.start(), edge.end());
    }
    return abs(area) / 2;
}

double lgm::Polygon::perimeter() const {
    double perimeter = 0;
    for (const auto &edge : edges_) {
        perimeter += edge.length();
    }
    return perimeter;
}

bool lgm::Polygon::contains(const lgm::Point &p) const {
    Point left = p;
    left.x = -1e5;

    size_t numberOfCrosses = 0;

    for (const auto & edge : edges_) {
        Direction p_sgn    = ccw(edge, p);
        Direction left_sgn = ccw(edge, left);

        // Point is on border
        if (p_sgn == Direction::COLLINEAR && onSegment(edge, p))
            return true;

        if (p_sgn != left_sgn && p.y > std::min(edge.start().y, edge.end().y) &&
            p.y <= std::max(edge.start().y, edge.end().y)) {
            numberOfCrosses++;
        }
    }
    return (numberOfCrosses % 2 == 1);
}

bool lgm::Polygon::isBoundary(const lgm::Point &p) const {
    for (const auto & edge : edges_) {
        Direction p_sgn = ccw(edge, p);
        if (p_sgn == Direction::COLLINEAR && onSegment(edge, p))
            return true;
    }
    return false;
}

void lgm::Polygon::add(const lgm::Point &p) {
    if (ccw(edges_.back(), p) == Direction::COLLINEAR)
        throw std::invalid_argument("Three consecutive collinear points are not supported yet");
    vertices_.emplace_back(p);
    edges_.pop_back();
    edges_.emplace_back(vertices_[vertices_.size() - 2], vertices_.back());
    edges_.emplace_back(vertices_.back(), vertices_.front());
}

const std::vector<lgm::Point> &lgm::Polygon::vertices() const {
    return vertices_;
}

const std::vector<lgm::RefSegment> &lgm::Polygon::edges() const {
    return edges_;
}

size_t lgm::Polygon::size() const {
    return vertices_.size();
}

bool lgm::isConvex(const std::vector<lgm::Point> &vertices) {
    lgm::Direction origin_sgn = ccw(vertices[vertices.size() - 2], vertices.back(), vertices[0]);
    lgm::Direction sgn = ccw(vertices.back(), vertices[0], vertices[1]);
    for (unsigned int i = 2; i < vertices.size(); ++i) {
        if (sgn != origin_sgn) return false;
        sgn = ccw(vertices[i - 2], vertices[i - 1], vertices[i]);
    }
    return !(sgn != origin_sgn);
}

lgm::Point lgm::calculateInsidePoint(const std::vector<lgm::Point>& vertices) {
    if (vertices.size() < 3)
        throw std::logic_error("Inside point can be found only in >= 3 vertices.");
    if (lgm::ccw(vertices[0], vertices[1], vertices[2]) == lgm::Direction::COLLINEAR)
        throw std::logic_error("Three consecutive cannot be collinear");

    lgm::Point z;
    z.x = (vertices[0].x + vertices[1].x + vertices[2].x) / 3.0;
    z.y = (vertices[0].y + vertices[1].y + vertices[2].y) / 3.0;
    return z;
}
