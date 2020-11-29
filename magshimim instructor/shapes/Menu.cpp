#include "Menu.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

using myShapes::Rectangle;

const int SELECT_SHAPE = 0;
const int MOD_OR_INFO = 1;
const int CLEAR_ALL = 2;
const int EXIT = 9;

const int CIRCLE = 0;
const int RECTANGLE = 1;
const int TRIANGLE = 2;
const int ARROW = 3;

const int MOVE = 1;
const int VIEW = 2;
const int ERASE = 3;

Menu::Menu() 
{
}

Menu::~Menu()
{
}

void Menu::clearCanvas()
{
	for (int i=0; i<_shapes.size(); i++)
	{
		for (int i = 0; i < _shapes.size(); i++)
		{
			_shapes[i]->clearDraw(_canvas);
		}
	}
	_shapes.clear();
}

void Menu::addShapeMenu()
{
	cout << "Select option:\n\
	[0]-----new Circle\n\
	[1]-----new Rectangle\n\
	[2]-----new Triangle\n\
	[3]-----new Arrow\n\n\
	[5]-----Back to main menu\n";

	int input;
	cin >> input;
	string name;
	Circle* newCirc;//can't declare inside case
	double x1, x2, x3, y1, y2, y3;
	double len, wid;
	Triangle* t;
	myShapes::Rectangle* newRec;
	Arrow* arr;
	switch (input)
	{
	case CIRCLE:
		cout << "Enter x of center\n";
		double centerX;
		double centerY;
		double radius;
		cin >> centerX;
		cout << "Enter Y of center";
		cin >> centerY;
		cout << "Enter radius\n";
		cin >> radius;
		cout << "enter name\n";
		cin >> name;
		newCirc = new Circle(Point(centerX, centerY), radius, "Circle", name);
		_shapes.push_back(newCirc);
		_canvas.draw_circle(std::move(Point(centerX, centerY)), radius);

		break;
	case RECTANGLE:

		
		cout << "enter x of vertex\n";

		cin >> x1;
		cout << "enter y of vertex \n";
		cin >> y1;
		cout << "enter legnth\n";
		cin >> len;
		cout << "enter width\n";
		cin >> wid;

		cout << "enter name of rectangle\n";
		cin >> name;
	    newRec = new myShapes::Rectangle(Point(x1, y1), len, wid, "Rectangle", name);
		_shapes.push_back(newRec);
		_canvas.draw_rectangle(Point(x1, y1), Point(x1 + wid, y1 + len));
		break;
	case TRIANGLE:
		
		cout << "Enter x1, y1, x2,y2 and x3, y3\n";
		cin >> x1;
		cin >> y1;
		cin >> x2;
		cin >> y2;
		cin >> x3;
		cin >> y3;
		cout << "Enter name\n";
		cin >> name;
		t = new Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3), string("Triangle"), name);
		_shapes.push_back(t);
		_canvas.draw_triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3));
		break;
	case ARROW:
		cout << "Enter x1, y1, x2 and y2\n";
		cin >> x1;
		cin >> y1;
		cin >> x2;
		cin >> y2;
		cout << "Enter arrow name\n";
		cin >> name;
		arr = new Arrow(Point(x1, y1), Point(x2, y2), "Arrow", name);
		_shapes.push_back(arr);
		_canvas.draw_arrow(Point(x1, y1), Point(x2, y2));
		break;
	}
}


int input;
void Menu::mainMenu()
{
	while (input != EXIT)
	{
		using std::cout;
		using std::endl;
		cout << "Select option:\n\
	[0]-----Add a new shape\n\
	[1]-----Edit or get info for existing shape\n\
	[2]-----Clear canvas\n\
	[9]-----Exit\n";
		cin >> input;
		switch (input)
		{
		case SELECT_SHAPE:
			addShapeMenu();
			break;
		case MOD_OR_INFO:
			modInfoMenu();
			break;
		case CLEAR_ALL:
			clearCanvas();
			break;

		}
	}

	for (Shape* s : _shapes)
	{
		delete s;
		s = nullptr;
	}
	_shapes.clear();
}

void Menu::modInfoMenu()
{
	cout << "select shape to edit or it's information \n";
	for (int i=0; i < _shapes.size(); i++ )
	{
		cout << i << " . " << _shapes[i]->getType() << ": " << _shapes[i]->getName();
	}
	int input;
	int input2;
	cin >> input;
	int x=0; int y =0;
	if ( input >= 0 && input < _shapes.size())
	{
		cout << "Would you like to: [1] move, [2] view details, or [3] erase?\n";
		cin >> input2;
		Point* toMove;
		switch (input2)
		{
		case MOVE:
			cout << "enter x to move by\n";
			cin >> x;
			cout << "enter y to move by";
			cin >> y;
			_shapes[input]->clearDraw(_canvas);
			toMove = new Point(x, y);
			_shapes[input]->clearDraw(_canvas);
			_shapes[input]->move(*toMove);
			_shapes[input]->draw(_canvas);
			delete(toMove);
			break;
		case VIEW:
			_shapes[input]->printDetails();
			break;
		case ERASE:
			_shapes[input]->clearDraw(_canvas);
			_shapes.erase(_shapes.begin() + input);
		}
	}
	else
	{
		cout << "invalid input. returning to main menu\n";
	}
}


