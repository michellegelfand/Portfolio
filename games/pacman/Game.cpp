#include "Game.h"



Game::Game()
{
	//frame
	for (int y = 0; y < arenaWidth - 1; y++)
	{
		for (int x = 0; x < arenaHeight - 1; x++)
		{
			_board[y][x] = EDIBLE;

		}
	}

	for (int y = 0; y < arenaWidth; y++)
	{
		for (int x = 0; x < arenaHeight; x++)
		{
			if (y == 0 || y == arenaWidth - 1 || x == 0 || x == arenaHeight - 1)
			{
				_board[y][x] = WALL;

			}
		}

	}


	//inner mazes
	for (int y = 0; y < arenaWidth; y++)
	{
		for (int x = 0; x < arenaHeight; x++)
		{
			if (x ==3 && y < 15 && y > 5)//bottom left vertical
			{
				_board[y][x] = WALL;

			}
			if (y == 14 && x < 15 && x > 5)//bottom left horizonal
			{
				_board[y][x] = WALL;


			
			}
			if (y == 14 && x < 34 && x > 23)//bottom right horizonal
			{
				_board[y][x] = WALL;



			}

		
			if (x == 36 && y < 15 && y > 5)//bottom right vertical
			{
				_board[y][x] = WALL;

			}



			if ( (x==18||x==19||x == 20) && y < 17 && y > 11)//bottom middle vertical
			{
				_board[y][x] = WALL;

			}

			if ((x == 18 || x == 19 || x == 20) && y < 5 && y > 0)//upper middle vertical
			{
				_board[y][x] = WALL;

			}

			if (y == 10 && x < 28 && x > 10)//lower middle box vertical
			{
				_board[y][x] = WALL;

			}
			if (y == 6 && x < 28 && x > 10)//upper middle box vertical
			{
				_board[y][x] = WALL;

			}

			if ((x == 6 ) && y < 5 && y > 0)//upper left vertical
			{
				_board[y][x] = WALL;

			}
			if ((x == 33) && y < 5 && y > 0)//upper left verical
			{
				_board[y][x] = WALL;

			}
			if ((y == 4) && x < 13 && x > 5)//upper right horizontal
			{
				_board[y][x] = WALL;

			}
			if ((y == 4) && x < 33 && x > 25)//upper right horizontal
			{
				_board[y][x] = WALL;

			}
		
		}

	}
}