#pragma once
#include "Polygon.h"


namespace myShapes
{
	// Scoped becuase Rectangle is taken by global namespace.
	class Rectangle : public Polygon
	{
	public:
		// There's a need only for the top left corner 
		Rectangle(const Point& a, double length, double width, const std::string& type, const std::string& name);
		virtual ~Rectangle();

		virtual double getArea() const override;
		virtual double getPerimeter() const override;
		virtual void draw(const Canvas& canvas) override;
		virtual void clearDraw(const Canvas& canvas) override;

	private:
		double _length;
		double _width;
	};
}