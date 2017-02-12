#include "Units_disposer.h"

#include "interface/functions/functions.h"
#include "core/Network/Synchro_bends/Synchro_bends.h"
#include "interface/algorithms.h"
#include <core/Network/Node/InterfaceNode.h>
#include <core/Network/Interface/Input/Input.h>
//#include <core/Network/Node/Node.h>

namespace render {


Units_disposer::Units_disposer():
    placement_offset_multip{3}
{

}

void Units_disposer::dispose_interface_nodes(Input& input)
{
    static Point start_position{500, 500};
    static Point offset{Node::radius*3, 0};
    Point current_position{start_position};
    for (core::InterfaceNode node: input) {
        node.position() = current_position;
        current_position += offset;
    }
}


void Units_disposer::dispose_first_bends_according_to_its_nodes(std::vector<core::Bend>& bends) const
{
    static float step_length = Node::radius*placement_offset_multip;
    Point initial_offset{0,-step_length};
    for (core::Bend bend: bends) {
        core::Node master_node = bend.get_master_node();
        bend.position() = master_node.position() + initial_offset;
    }
}

void Units_disposer::dispose_bends_according_to_previous_placed_ones(
        Synchro_bends& placed_synchro_bends,
        Synchro_bends& new_synchro_bends) const
{
    static float step_length = Bend::radius*placement_offset_multip;
    std::vector<core::Bend>& bends = new_synchro_bends.get_bends();
    std::vector<core::Node> nodes_of_placed_bends =
            placed_synchro_bends.get_nodes();
    Point placed_nodes_center = get_center_among_of(nodes_of_placed_bends);
    Point placed_bends_center = get_center_among_of(placed_synchro_bends.get_bends());
    Point steps_offset =
            Point(placed_bends_center - placed_nodes_center)
            .normalized() * step_length;
    for (core::Bend bend: bends) {
        core::Node master_node = bend.get_master_node();
        Point offset_of_master = master_node.position() - placed_nodes_center;
        bend.position() = placed_bends_center + offset_of_master + steps_offset;
    }
}

void Units_disposer::dispose_bends(
        std::vector<core::InterfaceNode>& nodes,
        Synchro_bends& placed_synchro_bends,
        Synchro_bends& new_synchro_bends) const
{
    std::vector<core::Bend>& bends = new_synchro_bends.get_bends();
    if (bends.size() == 0) {
        return;
    }
    
    if (placed_synchro_bends.get_bends().size()) {
        dispose_bends_according_to_previous_placed_ones(placed_synchro_bends, new_synchro_bends);
    } else {
        dispose_first_bends_according_to_its_nodes(bends);
    }

}




}
