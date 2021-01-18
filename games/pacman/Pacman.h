#pragma once
#include "Player.h"


class Player;

class Pacman :
    public Player
{
public:
    Pacman(Game& game)  
        :Player(game)
    {
        _x=22;
        _y = 9;
    }
    virtual void behaviour() override;
    virtual ~Pacman() = default;

    
};

