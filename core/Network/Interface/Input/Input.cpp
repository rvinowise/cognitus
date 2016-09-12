#include "Input.h"

Input::Input()
{

}

void Input::fireSensor(int index)
{
    node[index]->fire();
}
