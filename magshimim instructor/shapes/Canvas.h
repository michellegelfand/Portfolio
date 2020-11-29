#pragma once

#include <vector>
#include "CImg.h"
#include "Point.h"

// Color enum structure representing all available colors on the system (supported subset of all colors)
enum class Color { red, green, blue, white, black };

/*
	This class is responsible for creating canvas, drawing shapes and removing shapes
*/
class Canvas {
public:
	/// <summary>
	/// Constructor for Canvas, initialized all required variables
	/// </summary>
	Canvas();

	/// <summary>
	/// Destructor for Canvas, dextruct  all required variables
	/// </summary>
	~Canvas();

	/// <summary>
	/// Drawing circle on canvas
	/// <param name="center">Center Point of the circle</param>
	/// <param name="radius">Radius of the circle</param>
	/// <param name="color">Color of the circle</param>
	/// </summary>
	void draw_circle(const Point& center, double radius, Color color=Color::blue) const;

	/// <summary>
	/// Drawing an arrow on canvas
	/// <param name="first_point">First Point of the arrow</param>
	/// <param name="second_point">Second Point of the arrow</param>
	/// <param name="color">Color of the arrow</param>
	/// </summary>
	void draw_arrow(const Point& first_point, const Point& second_point, Color color = Color::green) const;

	/// <summary>
	/// Drawing rectangle on canvas
	/// <param name="first_point">First Point of the rectangle</param>
	/// <param name="second_point">Second Point of the rectangle</param>
	/// <param name="color">Color of the rectangle</param>
	/// </summary>
	void draw_rectangle(const Point& first_point, const Point& second_point, Color color = Color::red) const;

	/// <summary>
	/// Drawing triangle on canvas
	/// <param name="first_point">First Point of the triangle</param>
	/// <param name="second_point">Second Point of the triangle</param>
	/// <param name="third_point">Third Point of the triangle</param>
	/// <param name="color">Color of the triangle</param>
	/// </summary>
	void draw_triangle(const Point& first_point, const Point& second_point, const Point& third_point, Color color = Color::white) const;

	/// <summary>
	/// Removing circle from canvas
	/// <param name="center">Center Point of the circle</param>
	/// <param name="radius">Radius of the circle</param>
	/// <param name="color">Color of the circle</param>
	/// </summary>
	void clear_circle(const Point& center, double radius) const;

	/// <summary>
	/// Removing arrow from canvas
	/// <param name="first_point">First Point of the arrow</param>
	/// <param name="second_point">Second Point of the arrow</param>
	/// <param name="color">Color of the arrow</param>
	/// </summary>
	void clear_arrow(const Point& first_point, const Point& second_point) const;

	/// <summary>
	/// Removing rectangle from canvas
	/// <param name="first_point">First Point of the rectangle</param>
	/// <param name="second_point">Second Point of the rectangle</param>
	/// <param name="color">Color of the rectangle</param>
	/// </summary>
	void clear_rectangle(const Point& first_point, const Point& second_point) const;

	/// <summary>
	/// Removing triangle from canvas
	/// <param name="first_point">First Point of the triangle</param>
	/// <param name="second_point">Second Point of the triangle</param>
	/// <param name="third_point">Third Point of the triangle</param>
	/// <param name="color">Color of the triangle</param>
	/// </summary>
	void clear_triangle(const Point& first_point, const Point& second_point, const Point& third_point) const;

private:
	std::vector<unsigned char> get_color(Color color) const;
	cimg_library::CImg<unsigned char>* _board;
	cimg_library::CImgDisplay* _disp;
};
