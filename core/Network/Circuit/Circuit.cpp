#include "Circuit.h"

#include "core/Network/Node/Node.h"

namespace core {

bool Sequence_pair::is_has_noise_bends_inside()
{
    if (
            (start().get_next_links_qty() == 0) ||
            (end().get_prev_links_qty() == 0)
            )
    {
        throw("not connected Bends inside one Line_of_circuit");
    }

    if (
            (start().get_next_links_qty() > 0) ||
            (end().get_prev_links_qty() > 0) ||
            (start().get_next_bend(0) != end().get_prev_bend(0))
            )
    {
        return true;
    }
    return false;
}

Activation_interval Sequence_pair::interval()
{
    return Activation_interval{
        start().interval().start, end().interval().end};
}



Circuit::Circuit()
{

}

Bend Circuit::getFirstStartBend()
{
    return first_sequence.start();
}
Bend Circuit::getFirstEndBend()
{
    return first_sequence.end();
}
Bend Circuit::getSecondStartBend()
{
    return last_sequence.start();
}
Bend Circuit::getSecondEndBend()
{
    return last_sequence.end();
}

void Circuit::putFirstStartBend(Bend bend)
{
    first_sequence.start() = bend;
}
void Circuit::putFirstEndBend(Bend bend)
{
    first_sequence.end() = bend;
}
void Circuit::putSecondStartBend(Bend bend)
{
    last_sequence.start() = bend;
}
void Circuit::putSecondEndBend(Bend bend)
{
    last_sequence.end() = bend;
}

bool Circuit::is_first_consequence_placed_inside_one_higher_node()
{
    if (first_sequence.start().get_common_higher_nodes_with(first_sequence.end()).size() > 0)
    {
        return true;
    }
    return false;
}

Node Circuit::create_higher_node_for_it()
{

}

bool Circuit::is_complete()
{
    return !
            (
                getFirstStartBend().is_empty() ||
                getFirstEndBend().is_empty() ||
                getSecondStartBend().is_empty() ||
                getSecondEndBend().is_empty()
                );
}



Sequence_pair Circuit::get_first_line()
{
    return first_sequence;
}

Sequence_pair Circuit::get_second_line()
{
    return last_sequence;
}



}
