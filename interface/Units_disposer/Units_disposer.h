#pragma once

#include "core/Network/Node/Bend/Bend.h"
#include "core/Network/Node/Node.h"

namespace render {



class Units_disposer
{
public:
    Units_disposer();

    void dispose_last_bend(core::Node node);
    void dispose_bend(core::Bend bend);
};


}
