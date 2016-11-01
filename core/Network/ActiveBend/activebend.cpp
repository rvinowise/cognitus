#include "ActiveBend.h"

namespace core {

void ActiveBends::connectThisBendsToOthers(ActiveBends *nextActiveBend)
{
    for (std::size_t i_bendFrom = 0; i_bendFrom < bend.size(); i_bendFrom++) {
        Bend* bendFrom = bend[i_bendFrom];
        for (std::size_t i_bendTo = 0; i_bendTo < nextActiveBend->bend.size(); i_bendTo++) {
            Bend* bendTo = nextActiveBend->bend[i_bendTo];

            bendFrom->connectTo(bendTo);
        }
    }
}

}
