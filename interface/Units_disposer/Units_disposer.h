#pragma once

#include "core/Network/Node/Bend/Bend.h"
#include "core/Network/Node/Node.h"

namespace core {
    class Synchro_bends;
    class InterfaceNode;
    class Input;
}

namespace render {



class Units_disposer
{
public:
    Units_disposer();

    void dispose_interface_nodes(Input &input);

    void dispose_first_bends_according_to_its_nodes(std::vector<core::Bend>& bends) const;
    void dispose_bends_according_to_previous_placed_ones(
            Synchro_bends& placed_synchro_bends,
            Synchro_bends& new_synchro_bends) const;
    void dispose_bends(std::vector<core::InterfaceNode> &nodes, Synchro_bends& placed_synchro_bends, Synchro_bends &new_synchro_bends) const;
    
private:
    float placement_offset_multip;
};


}
