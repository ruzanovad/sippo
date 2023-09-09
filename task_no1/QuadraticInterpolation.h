#include <functional>
#include "Point2D.h"

class Solver
{
private:
    std::function<double(double)> function;

public:
    Solver(std::function<double(double)> function) : function(function)
    {
    }
    Point2D solve(const double&, const double&, const double&, bool);
};