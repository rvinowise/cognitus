
#include "Bend.h"

#include "core/Node/Node.h"

#ifdef debug_mode
#include "core/Node/InterfaceNode.h"
#include "core/Network/Network.h"
#include "core/test/allTests.h"
#include "core/test/randomFunc.h"
#endif

namespace core {

Bend_data::Bend_data(Node& masterNode)
    :master_node(masterNode)
{

}


Bend::Bend()
{
    data = nullptr;
}

Bend::Bend(Node& masterNode)
{	
    data = new Bend_data(masterNode);
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

bool Bend::operator!=(const Bend &other) const
{
    return this->data != other.data;
}

void Bend::remove()
{
    for (std::vector<Bend>::iterator i_prevBend = data->prevBend.begin();
         i_prevBend != data->prevBend.end();
         i_prevBend++) {
        for (std::vector<Bend>::iterator i_nextOfPrevBend = i_prevBend->data->nextBend.begin();
             i_nextOfPrevBend != i_prevBend->data->nextBend.end();
             i_nextOfPrevBend++) {
            if (*i_nextOfPrevBend == *this) {
                i_prevBend->data->nextBend.erase(i_nextOfPrevBend);
                break;
            }
        }
    }
    for (std::vector<Bend>::iterator i_nextBend = data->nextBend.begin();
         i_nextBend != data->nextBend.end();
         i_nextBend++) {
        for (std::vector<Bend>::iterator i_prevOfNextBend = i_nextBend->data->prevBend.begin();
             i_prevOfNextBend != i_nextBend->data->prevBend.end();
             i_prevOfNextBend++) {
            if (*i_prevOfNextBend == *this) {
                i_nextBend->data->prevBend.erase(i_prevOfNextBend);
                break;
            }
        }
    }
}




bool Bend::is_this_last_bend_in_chain() const {
    return data->nextBend.empty();
}




void Bend::connect_to(Bend& toBend)
{
    this->data->nextBend.push_back(toBend);
    toBend.data->prevBend.push_back(Bend(*this));
}

bool Bend::is_empty() const
{
    return data == nullptr;
}

Node& Bend::get_master_node()
{
    return data->master_node;
}

Node& Bend::get_node_of_whole_figure()
{
    return data->node_of_whole_figure;
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
    return data->higher_figure_bends.size();
}

std::vector<Node> Bend::get_common_higher_nodes_with(Bend otherBend)
{
    std::vector<Node> commonNodes;
    for(Bend this_place: data->higher_figure_bends) {
        for (Bend other_place: otherBend.data->higher_figure_bends) {
            if (this_place.get_node_of_whole_figure()
                ==
                other_place.get_node_of_whole_figure())
            {
                commonNodes.push_back(this_place.get_node_of_whole_figure());
            }
        }
    }

    return commonNodes;
}

void Bend::append_to_higher_node(Node &inNode)
{

}

void Bend::copy_prev_bends_from(Bend otherBend)
{
    for(Bend bend: otherBend.data->prevBend) {
        data->prevBend.push_back(bend);
    }
}
void Bend::copy_next_bends_from(Bend otherBend)
{
    for(Bend bend: otherBend.data->nextBend) {
        data->nextBend.push_back(bend);
    }
}

void Bend::attach_to_bend_of_figure(Bend figureBend)
{
    this->data->higher_figure_bends.push_back(figureBend);
}

Bend Bend::add_next_bend()
{
    Bend newBend(this->get_master_node());
    data->nextBend.push_back(newBend);
    return newBend;
}

const std::vector<Bend>& Bend::get_array_of_prev_bends() const
{
    return data->prevBend;
}
const std::vector<Bend>& Bend::get_array_of_next_bends() const
{
    return data->nextBend;
}

void Bend::erase_prev_bend(std::size_t index)
{
    data->prevBend.erase(data->prevBend.begin() + index);
}
void Bend::erase_next_bend(std::size_t index)
{
    data->nextBend.erase(data->nextBend.begin() + index);
}





}


