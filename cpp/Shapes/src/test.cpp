#include <stdio.h>
#include <mcheck.h>
#include <vector>
#include <iostream>

#include "glut_utils.h"
#include "shape.h"
#include "line.h"
#include "point.hpp"
#include "circle.h"
#include "square.h"
#include "rectangle.h"
#include "composit.h"

using namespace ilrd;

static void DrawFunction();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();

Line line(500);
Square square(500);
Rectangle rectangle(300, 500);
Circle circle(140);
Composite composite;

Point p(220,220);
Point p2(600, 440);
Point p3(700,200);
Point p4(100,100);
/**composit shapes**/
Circle circlecomp(80);
Square squarecomp(20);
Rectangle rectanglecomp(40, 60);
Rectangle rectanglecomp2(300, 12);


Composite com2;
Square sqr2(40);
Circle crc2(30);

double angle = 20;
std::vector<Shape*> shapes;

int main(int argc, char** argv)
{
    shapes.push_back(&line);
    shapes.push_back(&square);
    shapes.push_back(&rectangle);
    shapes.push_back(&circle);
    shapes.push_back(&composite); 

    shapes[0]->SetPosition(p2);
    shapes[0]->SetColor(Shape::GREEN);
    shapes[1]->SetPosition(p);
    shapes[1]->SetColor(Shape::RED);
    shapes[2]->SetAngle(40);
    shapes[2]->SetPosition(p3);
    shapes[2]->SetColor(Shape::BLUE);

    crc2.SetPosition(p3);
    sqr2.SetPosition(p3);

    com2.AddShape(&crc2);
    com2.AddShape(&sqr2);

    circlecomp.SetPosition(p3);
    squarecomp.SetPosition(p3);
    circlecomp.SetColor(Shape::CYAN);
    squarecomp.SetColor(Shape::CYAN);
    circle.SetPosition(p2);
    rectanglecomp.SetPosition(p3);
    rectanglecomp2.SetPosition(p3);
    rectanglecomp.SetColor(Shape::CYAN);
    rectanglecomp2.SetColor(Shape::CYAN);

    composite.AddShape(&circlecomp);
    composite.AddShape(&squarecomp);
    composite.AddShape(&rectanglecomp);
    composite.AddShape(&rectanglecomp2);

    composite.SetAngle(90);
    composite.SetColor(Shape::CYAN);
    com2.SetAngle(60);
    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 10);

    DrawMainLoop(); 

    std::cout << composite.GetAngle() << std::endl;
    std::cout << composite.GetColor() << std::endl;

    printf("exit\n");

    return 0;
}


static void DrawFunction()
{
    line.Draw();
    square.Draw();
    rectangle.Draw();
    circle.Draw();
    composite.Draw(); 
    com2.Draw();
}


static int KeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}


static int MouseFunction(int button, int state, int x, int y)
{
    /* printf("Mouse: %d,%d,%d,%d\n", button, state, x, y); */
    (void)y;
    (void)x;
    if (state == 1 && button == MOUSE_WHEEL_UP)
    {
        /* rCircle *= 1.1; */
        return 1;
    }
    if (state == 1 && button == MOUSE_WHEEL_DOWN)
    {
        /* rCircle *= 0.9; */
        return 1;
    }

    if (button == MOUSE_LEFT)
    {
        /* drawCircle = state; */
        return 1;
    }

    return 0;
}


static int MotionFunction(int x, int y)
{
    printf("Mouse: %d,%d\n", x, y);

    return 0;
}


static int TimerFunction()
{
    
    shapes[0]->SetAngle(angle);
    shapes[1]->Revolve(shapes[0]->GetPosition(), 0.03);
    shapes[1]->Revolve(shapes[2]->GetPosition(), 0.02);

    angle -=0.1;

    shapes[2]->Revolve(p2, 0.01);
    shapes[2]->Revolve(shapes[2]->GetPosition(), 0.07);

    shapes[3]->Revolve(p4, -0.06);
    composite.Revolve(p2, -0.8);
    /* composite.SetAngle(angle); */
    return 1;  /* draw */
}

