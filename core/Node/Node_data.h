#pragma once

#include <vector>

#include "core/Bend/Bend.h"
#include "core/Bend/Figure_bend/Figure_bend.h"
#include "core/auxiliary/Acquiring_handles/Acquiring_handles.h"

namespace core {

class Node_data: public Acquiring_handles
{
    friend class Node;
    Node_data();

private:
    std::vector<Bend> bend;
    Figure_bend lower_chain_bend;
};





}
