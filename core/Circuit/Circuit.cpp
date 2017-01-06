#include "Circuit.h"

#include "core/Node/Node.h"

namespace core {

Circuit::Circuit()
{

}

Bend Circuit::getFirstStartBend()
{
    return firstLine.start;
}
Bend Circuit::getFirstEndBend()
{
    return firstLine.end;
}
Bend Circuit::getSecondStartBend()
{
    return secondLine.start;
}
Bend Circuit::getSecondEndBend()
{
    return secondLine.end;
}

void Circuit::putFirstStartBend(Bend bend)
{
    firstLine.start = bend;
}
void Circuit::putFirstEndBend(Bend bend)
{
    firstLine.end = bend;
}
void Circuit::putSecondStartBend(Bend bend)
{
    secondLine.start = bend;
}
void Circuit::putSecondEndBend(Bend bend)
{
    secondLine.end = bend;
}

bool Circuit::is_first_consequence_placed_inside_one_higher_node()
{
    if (firstLine.start.get_common_higher_nodes_with(firstLine.end).size() > 0)
    {
        return true;
    }
    return false;
}

Node Circuit::create_higher_node_for_it()
{

}



}
