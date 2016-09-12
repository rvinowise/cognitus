#pragma once

#include "core/Network/Network.h"
#include "sprites/spriteIndexes.h"

#include "../gameEngine/spriteEngine/SpriteView.h"

class Visualisator
{
public:
    Visualisator();
    void init();

    void draw();
	
    int STEP;
private:
    SpriteView spriteView;
};
