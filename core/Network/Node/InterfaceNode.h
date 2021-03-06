#pragma once

#include "core/Network/Node/Node.h"

#include <vector>

namespace core {

struct InterfaceNode_data
{
    InterfaceNode_data();

    bool is_prepared_to_fire;
    std::size_t index_in_interface_array;
};

class InterfaceNode: public Node
{
public:
    InterfaceNode();
    InterfaceNode(const Node& other);
    InterfaceNode(const InterfaceNode &other);
    void create_data();

    void prepare_to_fire();
    bool is_prepared_to_fire();
    core::Bend fire() override;

    void set_index_in_interface_array(std::size_t index);
    std::size_t get_index_in_interface_array() const;

private:
    InterfaceNode_data* interface_data;
};


}
