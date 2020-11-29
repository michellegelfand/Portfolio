#include "Polygon.h"
#include <string>

class Triangle : public Polygon
{
public:
	Triangle(const Point& a, const Point& b, const Point& c, const std::string& type, const std::string& name);
	virtual ~Triangle();

	virtual double getArea() const override;
	virtual double getPerimeter() const override;

	
	virtual void draw(const Canvas& canvas) override;
	virtual void clearDraw(const Canvas& canvas) override;
	
};