#include "Units_disposer.h"

#include "interface/functions/functions.h"

namespace render {


Units_disposer::Units_disposer()
{

}


void dispose_first_bend_for_node(core::Bend bend)
{
    static Point offset{0, -30};
    core::Node master_node = bend.get_master_node();
    bend.position() = master_node.position() + offset;
}

void dispose_bend_according_to_prev(core::Bend bend, core::Bend prev_bend)
{
    static Point offset{0, -30};
    bend.position() = prev_bend.position() + offset;
}

void Units_disposer::dispose_last_bend(core::Node node)
{
    if (node.bends().size() == 0) {
        throw("Units_disposer::dispose_last_bend for Node without Bends");
    }
    if (node.bends().size() == 1) {
        dispose_first_bend_for_node(node.bends().back());
    } else {
        core::Bend prev_bend =
                node.bends()[node.bends().size()-2];
        dispose_bend_according_to_prev(node.bends().back(), prev_bend);
    }
}


void Units_disposer::dispose_bend(core::Bend bend)
{
    /*Node master_node = bend.get_master_node();
    Bend prev_bend = master_node.bends().;
    bend.position() =*/
}


}
