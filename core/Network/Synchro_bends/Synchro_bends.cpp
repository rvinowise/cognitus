#include "Synchro_bends.h"

#include "core/Network/Node/Node.h"

namespace core {

void Synchro_bends::connect_this_bends_to_others(Synchro_bends& next)
{
    for (std::size_t i_bendFrom = 0; i_bendFrom < bends.size(); i_bendFrom++) {
        Bend bendFrom = bends[i_bendFrom];
        for (std::size_t i_bendTo = 0; i_bendTo < next.bends.size(); i_bendTo++) {
            Bend bendTo = next.bends[i_bendTo];

            bendFrom.connect_to(bendTo);
        }
    }
}

std::vector<Bend>& Synchro_bends::get_bends()
{
    return bends;
}

std::vector<core::Node> Synchro_bends::get_nodes()
{
    std::vector<core::Node> result;
    for (Bend bend: bends) {
        result.push_back(bend.get_master_node());
    }
    return result;
}

}
