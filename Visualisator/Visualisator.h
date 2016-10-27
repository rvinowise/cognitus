#pragma once

#include "core/Network/Network.h"
#include "sprites/spriteIndexes.h"

#include "../gameEngine/spriteEngine/SpriteView.h"

class Visualisator
{
public:
    Visualisator(Network* network);
    void init();

    void draw();
	
    int STEP;
private:
    Network *network;
    
    SpriteView spriteView;
};
