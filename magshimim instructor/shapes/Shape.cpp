#include "Shape.h"

Shape::Shape(const std::string& name, const std::string& type)
	:_type(type), _name(name)
{
}
void Shape::printDetails() const
{
	std::cout << "type: " << _type << std::endl;
	std::cout << "name: " << _name<< std::endl;
	std::cout << "area: " << getArea() << std::endl;
	std::cout << "perimeter: " << getPerimeter() << std::endl;
}
std::string Shape::getType() const
{
	return _type;
}
std::string Shape::getName() const
{
	return _name;
}