#include <algorithm>
#include <vector>
#include <fstream>
#include <exception>
#include <functional>
#include <iostream>
#include "QuadraticInterpolation.h"

Point2D Solver::solve(const double &a, const double &b, const double &EPS = 1e-6, bool callback = true)
{
    if (a > b)
    {
        throw std::invalid_argument("a is bigger than b");
    }
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

    if (callback)
    {
        this->stream << "current values:\n";
        this->stream << "x\tf(x)\n";
        for (auto &x : list)
        {
            this->stream << x.getX() << " " << x.getY() << "\n";
        }
        this->stream << "\n";
    }

    while (std::abs(list[0].getX() - list[1].getX()) >= EPS)
    {

        if (!((list[1].getX() > list[0].getX()) ^ (list[2].getX() > list[0].getX())) &&
            ((list[1].getX() > list[0].getX()) ^ (list[3].getX() > list[0].getX())))
        {
            std::swap(list[2], list[3]);
        }
        list[3] = calculateDelta2(list[0], list[1], list[2]);
        sort(list.begin(), list.end(), [](const Point2D &a, const Point2D &b)
             { return a.getY() < b.getY(); });
        if (callback)
        {
            for (auto &x : list)
            {
                this->stream << x.getX() << " " << x.getY() << "\n";
            }
            this->stream << "\n";
        }
    }
    this->stream << list[0].getX() << " " << list[0].getY() << "\n";

    return list[0];
}