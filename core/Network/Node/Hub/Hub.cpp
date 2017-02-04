#include "Hub.h"

#include "Hub_data.h"

#include "core/Network/Node/Node_data.h"
#include "core/Network/Node/Hub/Iterator/Iterator_BFS.h"

namespace core {


Hub_data::Hub_data():
    Acquiring_handles()
{
}

Hub_data::Hub_data(Node in_figure_node):
    figure_node(in_figure_node), Acquiring_handles()
{

}



Hub::Hub()
{
    data = nullptr;
}

Hub::Hub(Node in_figure_node)
{
    data = new Hub_data(in_figure_node);
}


Hub::Hub(const Hub &other)
{
    data = other.data;
    if (data) {
        data->connect_a_handle();
    }
}

Hub::~Hub()
{
    if (data) {
        data->disconnect_a_handle();
    }
}

Hub Hub::new_empty()
{
    Hub figure;
    return figure;
}

bool Hub::is_empty()
{
    return data==nullptr;
}

bool Hub::operator==(const Hub &other) const
{
    return data == other.data;
}
bool Hub::operator!=(const Hub &other)const
{
    return data != other.data;
}

Hub &Hub::operator=(const Hub &other)
{
    data = other.data;
    if (data) {
        data->connect_a_handle();
    }
    return *this;
}

std::size_t Hub::get_prev_links_qty() const
{
    return data->prev_bends.size();
}
std::size_t Hub::get_next_links_qty() const
{
    return data->next_bends.size();
}

std::vector<Hub>& Hub::get_arr_next_hubs() const
{
    return data->next_bends;
}


Node Hub::get_node_of_whole_figure()
{
    return data->figure_node;
}

bool Hub::is_this_last_bend_in_chain() const {
    return data->next_bends.empty();
}

Hub Hub::add_next_bend()
{
    data->next_bends.push_back(Hub());
    return data->next_bends.back();
}

void Hub::push_next_bend(Hub in_figure)
{
    data->next_bends.push_back(in_figure);
}

std::vector<Bend>& Hub::get_arr_free_bends()
{
    return data->free_bends;
}

#ifdef debug_mode
void Hub::letdown_new_bends_to_node(std::size_t qty, Node node)
{
    for (std::size_t i_bend=0; i_bend<qty; i_bend++) {
        data->free_bends.push_back(Bend(node));
    }
}

std::vector<Hub> Hub::get_arr_not_linked_hubs(std::vector<Hub> hubs)
{
    std::vector<Hub> result;
    for (Hub hub: hubs) {
        if (
                (hub!=(*this))&&
                (!hub.lead_to(*this))&&
                (!this->lead_to(hub))
            ) {
            result.push_back(hub);
        }
    }
    return result;
}

bool Hub::lead_to(Hub other)
{
    for (
         iterator_hub_BFS iter(*this);
         !iter.is_end();
         ++iter
         ) {
        if (*iter == other) {
            return true;
        }
    }
    return false;
}
#endif


}
