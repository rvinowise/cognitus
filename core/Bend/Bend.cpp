
#include "Bend.h"

#include "core/Node/Node.h"

#ifdef debug_mode
#include "core/Node/InterfaceNode.h"
#include "core/Network/Network.h"
#include "core/test/allTests.h"
#include "core/test/randomFunc.h"
#endif

namespace core {

Bend::Bend()
{

}

Bend::Bend(Node masterNode)
{	
    data = new Bend_data();
    data->node = masterNode;
}

Bend::Bend(const Bend& other)
{
    this->data = other.data;
}

Bend::Bend(Bend &&other)
{
    this->data = other.data;
}

Bend::~Bend()
{

}

Bend& Bend::operator=(const Bend &other)
{
    if (this != &other) { // is it necessery?
        this->data = other.data;
    }
    return *this;
}


bool Bend::operator==(const Bend &other) const
{
    return this->data == other.data;
}




bool Bend::is_this_last_bend_in_chain() const {
    return data->nextBend.empty();
}




void Bend::connect_to(Bend& toBend)
{
    this->data->nextBend.push_back(toBend);
    toBend.data->prevBend.push_back(Bend(*this));
}

bool Bend::isEmpty() const
{
    return data == nullptr;
}

Node Bend::getNode()
{
    return data->node;
}

std::size_t Bend::get_prev_bends_qty() const
{
    return data->prevBend.size();
}
std::size_t Bend::get_next_bends_qty() const
{
    return data->nextBend.size();
}

Bend Bend::get_prev_bend(std::size_t index) const
{
    if (index >= data->prevBend.size()) {
        throw std::out_of_range("Bend::getPrevBend gets wrong index of Bend");
    }
    return data->prevBend[index];
}
Bend Bend::get_next_bend(std::size_t index) const
{
    if (index >= data->nextBend.size()) {
        throw std::out_of_range("Bend::getNextBend gets wrong index of Bend");
    }
    return data->nextBend[index];
}

std::size_t Bend::get_higher_nodes_qty() const
{
    return data->place_in_node.size();
}

std::vector<Node> Bend::get_common_higher_nodes_with(Bend otherBend)
{
    std::vector<Node> commonNodes;
    for(Place_in_node this_place: data->place_in_node) {
        for (Place_in_node other_place: otherBend.data->place_in_node) {
            if (this_place.node == other_place.node) {
                commonNodes.push_back(this_place.node);
            }
        }
    }

    return commonNodes;
}

const std::vector<Bend>& Bend::get_array_of_prev_bends() const
{
    return data->prevBend;
}
const std::vector<Bend>& Bend::get_array_of_next_bends() const
{
    return data->nextBend;
}



}


