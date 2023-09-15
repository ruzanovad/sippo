// #include <iostream>
#include <functional>
#include <cassert>
#include <cmath>
#include "QuadraticInterpolation.h"
// #include "Point2D.h"

const bool CALLBACK = true;

void customAssert(std::function<double(double)> function, const double &a, const double &b,
                  Point2D expected, const double &EPS = 1e-6, std::ostream &stream = std::cout) {
    Point2D answer;
    Solver solver(function, stream);
    try {
        answer = solver.solve(a, b, EPS, CALLBACK);
    }
    catch (const std::exception &ex) {
        std::cout << ex.what() << "\n";
    }
    assert(abs(expected.getX() - answer.getX()) < EPS && abs(expected.getY() - answer.getY()));
}

int main() {
    std::function<double(double)>
            first_func = [](double x) { return 2 * x * x - exp(x); },
            second_func = [](double x) {
        return -log(x) * exp(-x);
    };
    customAssert(first_func,
                 1, 3.5, Point2D(.3575219, first_func), 1e-3);
    customAssert(second_func,
                 0, 2, Point2D(1.76322211, second_func), 1e-3);
}