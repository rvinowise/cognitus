#include "ActiveBend.h"

namespace core {

void ActiveBends::connect_this_bends_to_others(ActiveBends& nextActiveBend)
{
    for (std::size_t i_bendFrom = 0; i_bendFrom < bend.size(); i_bendFrom++) {
        Bend bendFrom = bend[i_bendFrom];
        for (std::size_t i_bendTo = 0; i_bendTo < nextActiveBend.bend.size(); i_bendTo++) {
            Bend bendTo = nextActiveBend.bend[i_bendTo];

            bendFrom.connect_to(bendTo);
        }
    }
}

}
