#pragma once

#include <vector>

#include "core/Bend/Bend.h"
#include "core/Bend/Figure_bend/Figure_bend.h"
#include "core/auxiliary/Acquiring_handles/Acquiring_handles.h"

namespace core {

class Node_data: public Acquiring_handles
{
public:
    Node_data();

    size_t level;
    std::vector<Bend> bends;
    std::vector<Figure_bend> figure_bends;
};





}
