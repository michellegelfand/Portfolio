#include <stdio.h>
#include <mcheck.h>

#include "glut_utils.h"


int drawCircle = 1;
int xCircle = 250;
int yCircle = 100;
double rCircle = 12;

int line1x = 150;
int line1y = 440;
int line2x = 300;
int line2y = 650;


static void DrawFunction();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();


int main(int argc, char** argv)
{
    /*--------------------------- mtrace(); */

    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 100);

    DrawMainLoop(); 

    printf("exit\n");

    return 0;
}


static void DrawFunction()
{
    /* printf("Drawing\n"); */

    /* draw rectangle */
    DrawPolygon(COLOR_MAGENTA, 2, line1x, line1y, line2x, line2y);

    if (drawCircle)
        DrawCircle(COLOR_FILL|COLOR_RED, xCircle, yCircle, rCircle);
        DrawCircle(COLOR_FILL|COLOR_YELLOW, xCircle, yCircle+10, rCircle+100);
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

    if (state == 1 && button == MOUSE_WHEEL_UP)
    {
        rCircle *= 1.1;
        return 1;
    }
    if (state == 1 && button == MOUSE_WHEEL_DOWN)
    {
        rCircle *= 0.9;
        return 1;
    }

    if (button == MOUSE_LEFT)
    {
        drawCircle = state;
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
    xCircle += 1;
    yCircle += 1;

    /* line1x +=1; */
    line1y +=1;
   /*  line2x +=1; */
    line2y += +1;


    return 1;  /* draw */
}
