#include "ActiveBend.h"

void ActiveBend::connectThisBendsToOthers(ActiveBend *nextActiveBend)
{
    for (int i_bendFrom = 0; i_bendFrom < bend.size(); i_bendFrom++) {
        Bend* bendFrom = bend[i_bendFrom];
        for (int i_bendTo = 0; i_bendTo < nextActiveBend->bend.size(); i_bendTo++) {
            Bend* bendTo = nextActiveBend->bend[i_bendFrom];

            bendFrom->connectTo(bendTo);
        }
    }
}
