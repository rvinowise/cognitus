
#include "Bend.h"

#include "core/Node/Node.h"
#include "Bend_data.h"

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
    masterNode.append_bend(*this);
}

Bend::Bend(const Bend& other)
{
    this->data = other.data;
    data->connect_a_handle();
}

Bend::Bend(Bend &&other)
{
    this->data = other.data;
    other.data = nullptr;
}

Bend::~Bend()
{
    if (data) {
        data->disconnect_a_handle();
    }
}

Bend& Bend::operator=(const Bend &other)
{
    if (data != other.data) {
        if (!is_empty()) {
            data->disconnect_a_handle();
        }
        data = other.data;
        data->connect_a_handle();
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
    for (std::vector<Bend>::iterator i_prevBend = data->prev_bends.begin();
         i_prevBend != data->prev_bends.end();
         i_prevBend++) {
        for (std::vector<Bend>::iterator i_nextOfPrevBend = i_prevBend->data->next_bends.begin();
             i_nextOfPrevBend != i_prevBend->data->next_bends.end();
             i_nextOfPrevBend++) {
            if (*i_nextOfPrevBend == *this) {
                i_prevBend->data->next_bends.erase(i_nextOfPrevBend);
                break;
            }
        }
    }
    for (std::vector<Bend>::iterator i_nextBend = data->next_bends.begin();
         i_nextBend != data->next_bends.end();
         i_nextBend++) {
        for (std::vector<Bend>::iterator i_prevOfNextBend = i_nextBend->data->prev_bends.begin();
             i_prevOfNextBend != i_nextBend->data->prev_bends.end();
             i_prevOfNextBend++) {
            if (*i_prevOfNextBend == *this) {
                i_nextBend->data->prev_bends.erase(i_prevOfNextBend);
                break;
            }
        }
    }
}









void Bend::connect_to(Bend &toBend)
{
    this->data->next_bends.push_back(toBend);
    toBend.data->prev_bends.push_back(Bend(*this));
}

bool Bend::is_empty() const
{
    return data == nullptr;
}

Node& Bend::get_master_node()
{
    return data->master_node;
}


std::size_t Bend::get_prev_links_qty() const
{
    return data->prev_bends.size();
}
std::size_t Bend::get_next_links_qty() const
{
    return data->next_bends.size();
}

Bend Bend::get_prev_bend(std::size_t index) const
{
    if (index >= data->prev_bends.size()) {
        throw std::out_of_range("Bend::getPrevBend gets wrong index of Bend");
    }
    return data->prev_bends[index];
}
Bend Bend::get_next_bend(std::size_t index) const
{
    if (index >= data->next_bends.size()) {
        throw std::out_of_range("Bend::getNextBend gets wrong index of Bend");
    }
    return data->next_bends[index];
}

std::size_t Bend::get_higher_nodes_qty() const
{
    return data->higher_figure_bends.size();
}

std::vector<Node> Bend::get_common_higher_nodes_with(Bend otherBend)
{
    std::vector<Node> commonNodes;
    for(auto this_place: data->higher_figure_bends) {
        for (auto other_place: otherBend.data->higher_figure_bends) {
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
    for(Bend bend: otherBend.data->prev_bends) {
        data->prev_bends.push_back(bend);
    }
}
void Bend::copy_next_bends_from(Bend otherBend)
{
    for(Bend bend: otherBend.data->next_bends) {
        data->next_bends.push_back(bend);
    }
}

void Bend::attach_to_figure(Figure_bend figureBend)
{
    this->data->higher_figure_bends.push_back(figureBend);
}

Bend Bend::add_next_bend()
{
    Bend newBend(this->get_master_node());
    data->next_bends.push_back(newBend);
    return newBend;
}

const std::vector<Bend>& Bend::get_array_of_prev_bends() const
{
    return data->prev_bends;
}
const std::vector<Bend>& Bend::get_array_of_next_bends() const
{
    return data->next_bends;
}

void Bend::erase_prev_bend(std::size_t index)
{
    data->prev_bends.erase(data->prev_bends.begin() + index);
}
void Bend::erase_next_bend(std::size_t index)
{
    data->next_bends.erase(data->next_bends.begin() + index);
}





}


