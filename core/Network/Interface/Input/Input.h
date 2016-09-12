#pragma once

#include "../Interface.h"


class Input: public Interface
{
public:
    Input();

    void fireSensor(int index);
};

