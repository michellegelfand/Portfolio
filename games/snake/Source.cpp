#include < iostream >
#include <windows.h>
#include <time.h>
#include < conio.h >
#include <vector>

using namespace std;

const int arenaWidth = 20;
const int arenaHeight = 17;

int snakeHead_x, snakeHead_y, fruitX, fruitY, score, tailLength=0;

bool gameover=0;
vector<int>tailX; //snake coordinates
vector<int>tailY;

#define LEFT 'a'
#define RIGHT 'd' // Controls
#define UP 'w'
#define DOWN 's'

char movement;

void Setup() {
	
	srand(time(0));
	gameover = false;
	score = 0;

	snakeHead_x = (rand()%arenaWidth-1) +1;

	snakeHead_y = (rand()% arenaHeight - 1) + 1;

	fruitX = (rand() % arenaWidth - 1) + 1; //display fruit in a random place
	fruitY = (rand() % arenaHeight - 1) + 1;

}


void ClearScreen() {
	// Function which cleans the screen without flickering
	COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}



void Draw() {
	ClearScreen();

	//top of arena
	for (int i = 0; i < (arenaWidth + 2) / 2 + 1; i++)
	{
		cout << "\033[33m{}";
	}
	cout << endl;

	//check every place in arena if needs drawing
	for (int i = 0; i < arenaHeight; i++)
	{
		for (int j = 0; j < arenaWidth; j++) 
		{
			if (j == 0)
			{
				cout << "\033[33m{}"; //walls
			}
			if (i == snakeHead_y && j == snakeHead_x)
			{
				cout << "\033[32;1mO\033[0m"; 
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "\033[31m@\033[0m"; 
			}
			else 
			{
				bool drewHere = false;

				for (int k = 0; k < tailLength; k++) {

					if (tailX[k] == j && tailY[k] == i) {

						cout << "\033[32mO\033[0m"; 
						drewHere = true;
					}

				}

				if (!drewHere)
				{
					cout << " ";
				}
			}

			if (j == arenaWidth - 1)
			{
				cout << "\033[33m{}";
			}
		}

		cout << endl;

	}
	//reached bottom of arena, draw bottom walls
	for (int i = 0; i < (arenaWidth + 2) / 2 + 1; i++)
	{
		cout << "\033[33m{}";
	}
	cout << endl;

	cout << "\033[1m\033[36mScore:" << score << "\033[0m"<<endl;

}

void Input()
{
	if (_kbhit()) {

		switch (_getch()) {

		case LEFT:
			movement = LEFT;
			break;

		case RIGHT:
			movement = RIGHT;
			break;

		case UP:
			movement = UP;
			break;

		case DOWN:
			movement = DOWN;
			break;

		}

	}
	switch (movement) {

	case LEFT:
		snakeHead_x--;
		break;

	case RIGHT:
		snakeHead_x++;
		break;

	case UP:
		snakeHead_y--;
		break;

	case DOWN:
		snakeHead_y++;
		break;

	}

}

void driver()
{

	tailX.insert(tailX.begin(), snakeHead_x);

	tailY.insert(tailY.begin(), snakeHead_y);

	tailX.resize(tailLength+1);
	tailY.resize(tailLength+1);
	
	if (snakeHead_x >= arenaWidth || snakeHead_x <= -2)
	{
		gameover = true;
	}

	if (snakeHead_y >= arenaHeight || snakeHead_y <= -2)
	{
		gameover = true;
	}

	//check if sname bit itself
	for (int i = 1; i < tailLength; i++)
	{//start from 1 because 0 is head
		if (tailX[i] == snakeHead_x && tailY[i] == snakeHead_y)
			gameover = true;
	}
	if (snakeHead_x == fruitX && snakeHead_y == fruitY) {

		score += 10;

		fruitX = rand() % arenaWidth;

		fruitY = rand() % arenaHeight;

		tailLength++;

	}

}

int main()
{
	Setup();

	while (!gameover) {

		Draw();
		Sleep(100);

		Input();

		driver();
	}

	if (gameover)
	{
		cout << "____  ____  _  _ ____     ____  _  _ ____ ____\n";
		cout << "| __ | __| |\\/| |___    |    | |  | |___ | __/\n";
		cout << "|__] |   | |  | |___    |____|  \\/  |___ |  \\\n";
	}


	return 0;

}
