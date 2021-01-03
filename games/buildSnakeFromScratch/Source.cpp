#include < iostream >
#include <windows.h>
#include <time.h>
#include < conio.h >
#include <vector>

#include "Player.h"
#include "Pacman.h"
#include "Blinky.h"
#include "Clyde.h"

using namespace std;

const int arenaWidth = 17;
const int arenaHeight = 40;

int score = 0;
bool gameover = 0;


#define LEFT 'a'
#define RIGHT 'd' // Controls
#define UP 'w'
#define DOWN 's'

#define WALL '+'
#define EDIBLE '\''

Game game;
Pacman pacman(game);
Blinky blinky(game, &pacman);
Clyde clyde(game);


void ClearScreen() {
	// Function which cleans the screen without flickering
	COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}



void Draw() {
	ClearScreen();

	//check every place in arena if needs drawing
	for (int i = 0; i < arenaWidth; i++)
	{
		for (int j = 0; j < arenaHeight; j++)
		{

			if(game._board[i][j] == WALL)
			{
				cout << "\x1B[37m" << game._board[i][j];
			}
			else if (blinky.getX() == j&& blinky.getY() == i)
			{
				cout << "\033[31mO";
			}
			else if (clyde.getX() == j && clyde.getY() == i)
			{
				cout << "\x1B[35mO\033[m";
			}
			else if (pacman.getX() == j && pacman.getY() == i)
			{
				cout << "\x1B[33mO\033[0m";
			}
			else if(game._board[i][j] == EDIBLE ||game. _board[i][j] == ' ')
			{
				cout << "\033[34m"<<game._board[i][j];
			}
		}
		
		cout << endl;

	}


	cout << "\033[1m\033[36mScore:" << score << "\033[0m" << endl;

}


void driver()
{
	if (game._board[pacman.getY()][pacman.getX()]== EDIBLE)
	{
		game. _board[pacman.getY()][pacman.getX()] = ' ';
		score += 5;
	}
}




int main()
{

	while (1)
	{
		Draw();
		Sleep(100);
		pacman.behaviour();
		blinky.behaviour();
		clyde.behaviour();
		driver();
	}
	return 0;
}