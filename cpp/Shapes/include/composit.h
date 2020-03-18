 #ifndef  __COMPOSIT_H__
#define  __COMPOSIT_H__

#include <vector>

#include "../include/shape.h"

namespace ilrd
{

class Composite: public Shape
{
public:
    explicit Composite();

    virtual ~Composite();

    void AddShape(Shape* new_shape);

    virtual void SetPosition(const Point& position);
    
    virtual void SetColor(color_t color);

    virtual void SetAngle(double angle);

    virtual void Revolve(const Point& axis, double angle);

private:
    virtual void DrawImp();
    std::vector<Shape*> m_shape_vector;

    Composite(const Composite &);
    Composite & operator =(const Composite &);
};

} //namespace ilrd

#endif // __COMPOSIT_H__