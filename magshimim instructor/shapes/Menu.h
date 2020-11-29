#pragma once
#include <iostream>
#include <vector>

#include "Shape.h"
#include "Canvas.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Arrow.h"
#include "Polygon.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Arrow.h"
#include "Triangle.h"
class Menu
{
public:

	Menu();
	~Menu();
	void mainMenu();
	void addShapeMenu();
	void clearCanvas();
	void modInfoMenu();
private: 
	Canvas _canvas;
	std::vector<Shape*> _shapes;
};

