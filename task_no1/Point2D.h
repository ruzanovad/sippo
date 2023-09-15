#include <iostream>
#include <functional>

class Point2D
{
private:
    double x = 0., y = 0.;

public:
    Point2D()
    = default;
    Point2D(const double &x, const std::function<double(double)>& function) : x(x), y(function(x))
    {
    }
    Point2D(const double &x, const double &y) : x(x), y(y)
    {
    }

    double getX() const
    {
        return this->x;
    }
    double getY() const
    {
        return this->y;
    }
    void setX(const double &x)
    {
        this->x = x;
    }
    void setY(const double &y)
    {
        this->y = y;
    }
    void setPoint(const double &x, std::function<double(double)>& function)
    {
        this->x = x;
        this->y = function(x);
    }
    friend std::ostream &operator<<(std::ostream &stream, const Point2D &point)
    {
        stream << "Point(" << point.x << " " << point.y << ")";
        return stream;
    }
};
