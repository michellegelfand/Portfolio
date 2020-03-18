#ifndef  __SHAPE_H__
#define  __SHAPE_H__

#include <cmath>//M_PI

#include "glut_utils.h"
#include "point.hpp"


namespace ilrd
{

class Shape
{
public:
    enum color_t
    {
        RED     = COLOR_RED,
        GREEN   = COLOR_GREEN,
        BLUE    = COLOR_BLUE,
        YELLOW  = COLOR_YELLOW,
        MAGENTA = COLOR_MAGENTA,
        CYAN    = COLOR_CYAN,
        WHITE   = COLOR_WHITE,
        BLACK   = COLOR_BLACK,
        FILL    = COLOR_FILL
    };

    explicit Shape(Point position = Point(100, 100), double angle = 0,
                                                    color_t color = BLUE);
    virtual ~Shape();

    void Draw();
    virtual void SetPosition(const Point& position);
    Point GetPosition() const;
    
    virtual void SetColor(color_t color);
    color_t GetColor() const;

    virtual void SetAngle(double angle);
    double GetAngle() const;

    static double GetRadians(double angle);
    virtual void Revolve(const Point& axis, double angle);

private:
    virtual void DrawImp() = 0;
    Point m_position;
    double m_angle;
    color_t m_color;

protected:
    void InitDrawPolygon(size_t width, size_t height);
};

} // namespace ilrd

#endif /*__SHAPE_H__*/