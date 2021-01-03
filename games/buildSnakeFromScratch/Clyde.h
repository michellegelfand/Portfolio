#pragma once
#include "Player.h"




class Clyde : public Player
{
public:
    Clyde(Game& game) :Player(game){ _x = 35; _y = 13; };
    virtual ~Clyde() = default;
    virtual void behaviour() override;
private:
 
};

