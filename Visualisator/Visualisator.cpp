#include "Visualisator.h"




Visualisator::Visualisator(Network *network)
{
    STEP = 10;
    this->network = network;
}

void Visualisator::init()
{
    initSpriteInfo();
    spriteBase.loadSprites(pathToSprites, &spriteInfo);

    spriteView.setSprite(s_node);
}

/* the Network doesn't contain coordinates of its nodes, it's the
 Visualisator, who assigns it and drows images according to them. */
void Visualisator::draw()
{
    glPushMatrix();
    //glTranslate(QPointF(50,50));
    //glRotate(360);
    //spriteView.draw();
    network->input.getNodesQty();
    glPopMatrix();
	
}
