#pragma once
#include <qmap.h>
#include <qstring.h>

const int s_node = 0;
const int s_bend = 1;


extern QString pathToSprites;
extern QMap<int,QString> spriteInfo;
void initSpriteInfo();
