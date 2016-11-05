#include "Circuit.h"

namespace core {

Circuit::Circuit()
{

}

Bend* Circuit::getFirstStartBend()
{
    return firstLine.start;
}
Bend* Circuit::getFirstEndBend()
{
    return firstLine.end;
}
Bend* Circuit::getSecondStartBend()
{
    return secondLine.start;
}
Bend* Circuit::getSecondEndBend()
{
    return secondLine.end;
}

void Circuit::putFirstStartBend(Bend& bend)
{
    firstLine.start = &bend;
}
void Circuit::putFirstEndBend(Bend& bend)
{
    firstLine.end = &bend;
}
void Circuit::putSecondStartBend(Bend& bend)
{
    secondLine.start = &bend;
}
void Circuit::putSecondEndBend(Bend& bend)
{
    secondLine.end = &bend;
}



}
