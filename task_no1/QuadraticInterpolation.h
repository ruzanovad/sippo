#include <algorithm>
#include <vector>
#include <fstream>
#include <exception>
#include <functional>
#include <iostream>
#include "Point2D.h"

class Solver
{
private:
    std::function<double(double)> &function;
    std::ostream &stream;

public:
    Solver(std::function<double(double)> &function, std::ostream &stream) : function(function), stream(stream){};
    Point2D solve(const double &, const double &, const double &, bool);
};