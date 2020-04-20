#include "include/LGeometry.h"
#include "TestRunner.h"

#include <stdexcept>

using namespace lgm;

void TestPolygonContains();
void TestPolygonOnBoundary();
void TestConvex();
void TestConvexContains();
void TestConvexOnBoundary();
void TestConvexHull();
void TestSegmentIntersection();

int main() {
    {
        test::TestRunner tr;
        RUN_TEST(tr, TestPolygonContains);
        RUN_TEST(tr, TestPolygonOnBoundary);
        RUN_TEST(tr, TestConvex);
        RUN_TEST(tr, TestConvexContains);
        RUN_TEST(tr, TestConvexOnBoundary);
        RUN_TEST(tr, TestConvexHull);
        RUN_TEST(tr, TestSegmentIntersection);
    }
    return 0;
}
void TestPolygonContains() {
    std::vector<Point> vertices(5);
    vertices[0] = Point(-3, -1);
    vertices[1] = Point(3, -1);
    vertices[2] = Point(3, 5);
    vertices[3] = Point(0, 2);
    vertices[4] = Point(-3, 4);

    Polygon polygon(vertices);
    Point a(1, 3);
    Point b(-1, 3);
    Point c(0, 0);
    Point d(-2, 3);
    ASSERT_EQ(polygon.contains(a), true); // it's on boundary
    ASSERT_EQ(polygon.contains(b), false);
    ASSERT_EQ(polygon.contains(c), true);
    ASSERT_EQ(polygon.contains(d), true);
}

void TestPolygonOnBoundary() {
    std::vector<Point> vertices(5);
    vertices[0] = Point(-3, -1);
    vertices[1] = Point(3, -1);
    vertices[2] = Point(3, 5);
    vertices[3] = Point(0, 2);
    vertices[4] = Point(-3, 4);

    Polygon polygon(vertices);
    Point a(1, 3);
    Point b(-1, 3);
    Point c(0, 0);
    Point d(-2, 3);
    ASSERT_EQ(polygon.isBoundary(a), true); // it's on boundary
    ASSERT_EQ(polygon.isBoundary(b), false);
    ASSERT_EQ(polygon.isBoundary(c), false);
    ASSERT_EQ(polygon.isBoundary(d), false);
}

void TestConvex() {
    {
        std::vector<Point> vertices(5);
        vertices[0] = Point(-3, -1);
        vertices[1] = Point(3, -1);
        vertices[2] = Point(3, 5);
        vertices[3] = Point(0, 2);
        vertices[4] = Point(-3, 4);
        ASSERT_EQ(isConvex(vertices), false);
    }
    {
        ASSERT_THROWS([]() {
            std::vector<Point> vertices(5);
            vertices[0] = Point(-3, -1);
            vertices[1] = Point(3, -1);
            vertices[2] = Point(3, 5);
            vertices[3] = Point(0, 2);
            vertices[4] = Point(-3, 4);
            ConvexPolygon convex(vertices);
        }, std::logic_error("Trying to create ConvexPolygon from non-convex set of vertices."));
    }
    {
        std::vector<Point> vertices(5);
        vertices[0] = Point(-2, -3);
        vertices[1] = Point(1, -4);
        vertices[2] = Point(3, -2);
        vertices[3] = Point(2, 1);
        vertices[4] = Point(-2, 1);
        ASSERT_EQ(isConvex(vertices), true);
    }
}

void TestConvexContains() {
    std::vector<Point> vertices(5);
    vertices[0] = Point(-2, -3);
    vertices[1] = Point(1, -4);
    vertices[2] = Point(3, -2);
    vertices[3] = Point(2, 1);
    vertices[4] = Point(-2, 1);

    ConvexPolygon convex(vertices);

    Point a(2, -3);
    Point b(3, 0);
    Point c(0, 0);
    Point d(2, -1);

    ASSERT_EQ(convex.contains(a), true);
    ASSERT_EQ(convex.contains(b), false);
    ASSERT_EQ(convex.contains(c), true);
    ASSERT_EQ(convex.contains(d), true);
}

void TestConvexOnBoundary() {
    std::vector<Point> vertices(5);
    vertices[0] = Point(-2, -3);
    vertices[1] = Point(1, -4);
    vertices[2] = Point(3, -2);
    vertices[3] = Point(2, 1);
    vertices[4] = Point(-2, 1);

    ConvexPolygon convex(vertices);

    Point a(2, -3);
    Point b(3, 0);
    Point c(0, 0);
    Point d(2, -1);

    ASSERT_EQ(convex.isBoundary(a), true);
    ASSERT_EQ(convex.isBoundary(b), false);
    ASSERT_EQ(convex.isBoundary(c), false);
    ASSERT_EQ(convex.isBoundary(d), false);
}

void TestSegmentIntersection() {
    {
        Segment a(Point(0, 0), Point(5, 5));
        Segment b(Point(0, 6), Point(6, 0));

        ASSERT_EQ(intersects(a, b), true);
        Point c = calculateIntersection(a, b);
        ASSERT_EQ(c, Point(3, 3));
    }
    {
        Segment a(Point(0, 0), Point(5, 5));
        Segment b(Point(5, 0), Point(3, 2));
        ASSERT_EQ(intersects(a, b), false);
        ASSERT_THROWS([]() {
            Segment a(Point(0, 0), Point(5, 5));
            Segment b(Point(5, 0), Point(3, 2));
            calculateIntersection(a, b);
        }, std::logic_error(""));
    }
}

void TestConvexHull() {
    std::vector<Point> vertexes(15);
    vertexes[0] = Point(-10, 2);
    vertexes[1] = Point(-7, 2);
    vertexes[2] = Point(-4, 3);
    vertexes[3] = Point(-6, 5);
    vertexes[4] = Point(-8, 7);
    vertexes[5] = Point(-2, 8);
    vertexes[6] = Point(2, 3);
    vertexes[7] = Point(4, 5);
    vertexes[8] = Point(6, 1);
    vertexes[9] = Point(7, -5);
    vertexes[10] = Point(2, -7);
    vertexes[11] = Point(-4, -4);
    vertexes[12] = Point(-8, -6);
    vertexes[13] = Point(-7, -1);
    vertexes[14] = Point(2, 6);

    ConvexPolygon result = ModifiedGrahamScan(vertexes);
    ASSERT_EQ(result.size(), 8);
    ASSERT_EQ(isConvex(result.vertices()), true);
}