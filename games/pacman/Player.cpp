#include "Player.h"

Player::Player(Game& game)
	:_game(game)
{
}

bool Player::isClearOFWall(char movement)
{
	if (movement == LEFT && _game._board[_y][_x - 1] != _game.WALL)
	{
		return true;	
	}
	else if (movement == RIGHT && _game._board[_y][_x +1 ] != _game.WALL)
	{
		return true;
	}
	else if (movement == UP && _game._board[_y-1][_x ] != _game.WALL)
	{
		return true;
	}
	else if (movement == DOWN && _game._board[_y + 1][_x] != _game.WALL)
	{
		return true;
	}

	return false;
}
