#include "QuadraticInterpolation.h"
#include <algorithm>
#include <vector>
#include "Point2D.h"

Point2D Solver::solve(const double &a, const double &b, const double &EPS = 1e-6, bool callback=true)
{

    auto f = this->function;
    double h = (b - a) * 0.2;
    Point2D x1(a, f), x2(a + h, f), x3;
    if (x1.getY() < x2.getY())
        x3.setPoint(a - h, f);
    else
        x3.setPoint(a + 2 * h, f);
    auto calculateDelta = [&f](
                              const Point2D &x1, const Point2D &x2, const Point2D &x3) -> Point2D
    {
        return Point2D(.5 * ((
                                 x1.getY() * (x2.getX() * x2.getX() - x3.getX() * x3.getX()) +
                                 x2.getY() * (x3.getX() * x3.getX() - x1.getX() * x1.getX()) +
                                 x3.getY() * (x1.getX() * x1.getX() - x2.getX() * x2.getX())) /
                             (x1.getY() * (x2.getX() - x3.getX()) +
                              x2.getY() * (x3.getX() - x1.getX()) +
                              x3.getY() * (x1.getX() - x2.getX()))),
                       f);
    };
    auto calculateDelta2 = [&f](
                               const Point2D &x1, const Point2D &x2, const Point2D &x3) -> Point2D
    {
        return Point2D(0.5 * (x1.getX() + x2.getX()) + 0.5 *
                                                           (x1.getY() - x2.getY()) *
                                                           (x2.getX() - x3.getX()) *
                                                           (x3.getX() - x1.getX()) /
                                                           (x1.getY() * (x2.getX() - x3.getX()) +
                                                            x2.getY() * (x3.getX() - x1.getX()) +
                                                            x3.getY() * (x1.getX() - x2.getX())),
                       f);
    };
    Point2D delta = calculateDelta(x1, x2, x3);
    std::vector<Point2D> list = {x1, x2, x3, delta};
    sort(list.begin(), list.end(), [](const Point2D &a, const Point2D &b)
         { return a.getY() < b.getY(); });

    while (abs(list[0].getY() - list[1].getY()) >= EPS)
    {
        if (!((list[1].getY() > list[0].getY()) ^ (list[2].getY() > list[0].getY())) &&
            ((list[1].getY() > list[0].getY()) ^ (list[3].getY() > list[0].getY())))
        {
            std::swap(list[2], list[3]);
        }
        list[3] = calculateDelta2(list[0], list[1], list[2]);
        sort(list.begin(), list.end(), [](const Point2D &a, const Point2D &b)
             { return a.getY() < b.getY(); });
    }
    return list[0];
}