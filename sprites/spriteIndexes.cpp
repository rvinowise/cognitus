#include "spriteIndexes.h"
QString pathToSprites("C:/ydisk/program/cognitus/sprites/");
QMap<int,QString> spriteInfo;

void initSpriteInfo() {
    spriteInfo.insert(s_node,QString("node"));
    spriteInfo.insert(s_bend,QString("bend"));
}
