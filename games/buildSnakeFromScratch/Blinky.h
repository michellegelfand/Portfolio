#pragma once
#include "Player.h"
#include "Pacman.h"


class Blinky :
    public Player
{
public:
    Blinky(Game& game, Pacman* pm) : Player(game), _pm(pm) {  _x = 13; _y = 2; };
    virtual ~Blinky() = default;
    virtual void behaviour() override;

private:
    Pacman* _pm;
};

