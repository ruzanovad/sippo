// #include <iostream>
#include <functional>
#include <cassert>
#include <cmath>
#include <fstream>
#include "QuadraticInterpolation.h"
// #include "Point2D.h"

const bool CALLBACK = true;

void customAssert(std::function<double(double)> function, const double &a, const double &h,
                  Point2D expected, const double &EPS = 1e-6, std::ostream &stream = std::cout) {
    Point2D answer;
    Solver solver(function, stream);
    try {
        answer = solver.solve(a, h, EPS, CALLBACK);
        assert(abs(expected.getX() - answer.getX()));
        std::cout << "done" << "\n";
    }
    catch (const std::exception &ex) {
        std::cerr << ex.what() << "\n";
    }
}

int main() {
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
    std::function<double(double)>
            first_func = [](double x) { return 2 * x * x - exp(x); },
            second_func = [](double x) { return -log(x) * exp(-x); },
            third_func = [](double x) { return x * x * x * x - 14 * x * x * x + 60 * x * x - 70 * x; },
            fourth_func = [](double x) { return log(x) - exp(sin(x)); },
            fifth_func = [](double x) { return cos(x) + sin(exp(x)); };

    std::cout << "Test # 1" << "\n";
    // пример на странице 28
    customAssert(first_func,
                 1, 0.5, Point2D(.3575219, first_func), 1e-3);

    std::cout << "Test # 2" << "\n";
    // Пример на странцие 25
    customAssert(second_func,
                 0, 0.5, Point2D(1.76322211, second_func), 1e-3);

    std::cout << "Test # 3" << "\n";
    // Пример на странице 23, пришлось брать середину отрезка, т.к в ответе метода задается интервал
    customAssert(third_func,
                 0, 0.5, Point2D((.780804 + .7809753) * 0.5, third_func), 1e-5);

    // https://www.wolframalpha.com/input?i=y++%3D++ln%28x%29+-+e%5Esin%28x%29+minimum+on+%5B1%2C+6%5D
    std::cout << "Test # 4" << "\n";
    customAssert(fourth_func,
                 1, 0.1, Point2D(1.25922, fourth_func), 1e-5);

    std::cout << "Test # 5" << "\n";
    customAssert(fifth_func,
                 -5, 0.5, Point2D(-3.18303, fifth_func), 1e-5);

    std::cout << "Test # 6" << "\n";
    customAssert(fifth_func,
                 -4, 0.5, Point2D(-3.18303, fifth_func), 1e-5);
}