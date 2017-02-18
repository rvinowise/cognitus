
#include "Bend.h"

#include "core/Network/Node/Node.h"
#include "Bend_data.h"

#include "core/Network/Circuit/Circuit.h"


namespace core {

Bend_data::Bend_data(Node& masterNode)
    :master_node(masterNode)
{
    
}


Bend::Bend():
    data{nullptr}
{
}

Bend::Bend(Activation_interval interval)
{
#ifdef render_mode
    render::Bend::Drawable_unit::create_data();
#endif
    set_interval(interval);
}

Bend::Bend(Node& masterNode, std::size_t index_in_master_node)
{	
#ifdef render_mode
    render::Bend::Drawable_unit::create_data();
#endif
    data = new Bend_data(masterNode);
    data->index_in_master_node = index_in_master_node;
}

Bend::Bend(const Bend& other)
#ifdef render_mode
    :render::Bend(other)
#endif
{
    this->data = other.data;
}

Bend::Bend(Bend &&other)
#ifdef render_mode
    :render::Bend(std::move(other))
#endif
{
    this->data = other.data;
    other.data = nullptr;
}

Bend::~Bend()
{

}

Bend& Bend::operator=(const Bend &other)
{
#ifdef render_mode
    render::Bend::data = other.render::Bend::data;
#endif
    data = other.data;
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

bool Bend::executed_before_this(Bend in_bend) const
{
    return this->data->interval.end < in_bend.data->interval.start;
}

bool Bend::executed_after_this(Bend in_bend) const
{
    return this->data->interval.start > in_bend.data->interval.end;
}

Activation_interval Bend::interval()
{
    return data->interval;
}

void Bend::set_interval(Activation_interval in_interval)
{
    data->interval = in_interval;
}









void Bend::connect_to(Bend &toBend)
{
    this->data->next_bends.push_back(toBend);
    toBend.data->prev_bends.push_back(Bend(*this));
}

Bend Bend::incorporate_line_to_this_bend(Sequence_pair in_line)
{
    copy_prev_bends_from(in_line.start());
    copy_next_bends_from(in_line.end());
    set_interval(in_line.interval());
}

bool Bend::is_empty() const
{
    return data == nullptr;
}

Node& Bend::get_master_node()
{
    return data->master_node;
}
const Node& Bend::get_master_node() const
{
    return data->master_node;
}

std::size_t Bend::get_index_in_master_node() const
{
    return data->index_in_master_node;
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

Bend Bend::get_prev_brother_bend() const
{
    Node master_node = get_master_node();
    if (this->get_index_in_master_node() > 0) {
        return master_node.bends()[get_index_in_master_node()-1];
    }
    return Bend();
  
}

std::size_t Bend::get_higher_nodes_qty() const
{
    return data->higher_hubs.size();
}

std::vector<Node> Bend::get_common_higher_nodes_with(Bend otherBend)
{
    std::vector<Node> commonNodes;
    for(auto this_place: data->higher_hubs) {
        for (auto other_place: otherBend.data->higher_hubs) {
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

std::vector<Hub>& Bend::hubs()
{
    return data->higher_hubs;
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

void Bend::attach_to_hub(Hub hub)
{
    this->data->higher_hubs.push_back(hub);
}


const std::vector<Bend>& Bend::prev_bends() const
{
    return data->prev_bends;
}
std::vector<Bend>& Bend::next_bends()
{
    return data->next_bends;
}
const std::vector<Bend>& Bend::next_bends() const
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


