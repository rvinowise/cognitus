#include "Hub.h"

#include "Hub_data.h"

#include "core/Network/Node/Node_data.h"
#include "core/Network/Node/Hub/Iterator/Iterator_BFS.h"
#include "interface/algorithms.h"

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
    render::Hub::create_data();
}


Hub::Hub(const Hub &other)
#ifdef render_mode
    :render::Hub(other)
#endif
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
#ifdef render_mode
    render::Hub::Drawable_unit::data = other.render::Hub::Drawable_unit::data;
#endif
    return *this;
}

std::size_t Hub::get_prev_links_qty() const
{
    return data->prev_hubs.size();
}
std::size_t Hub::get_next_links_qty() const
{
    return data->next_hubs.size();
}

std::vector<Hub>& Hub::get_arr_next_hubs() const
{
    return data->next_hubs;
}


Node Hub::get_node_of_whole_figure()
{
    return data->figure_node;
}

bool Hub::is_this_last_bend_in_chain() const {
    return data->next_hubs.empty();
}

Hub Hub::add_next_bend()
{
    Hub hub;
    hub.create_data();
    data->next_hubs.push_back(hub);
    hub.data->prev_hubs.push_back(*this);
    return hub;
}

void Hub::push_next_hub(Hub in_hub)
{
    data->next_hubs.push_back(in_hub);
    in_hub.data->prev_hubs.push_back(*this);
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

std::vector<Hub> Hub::get_hubs_leading_to_this()
{
    std::vector<Hub> result;
    Node node = get_node_of_whole_figure();
    for (Hub hub: node) {
        if (hub.lead_to(*this)) {
            result.push_back(hub);
        }
    }
    return result;
}

std::vector<Hub> Hub::get_hubs_possible_for_linking(std::vector<Hub> hubs)
{
    std::vector<Hub> result;
    std::vector<Hub> hubs_leading_to_this;
    hubs_leading_to_this = this->get_hubs_leading_to_this();

    for (Hub hub: hubs) {
        bool must_be_superfluous_link = false;
        for (Hub prev_hub: hubs_leading_to_this) {
            if (prev_hub.lead_to(hub)) {
                must_be_superfluous_link = true;
            }
        }

        if (
                (!must_be_superfluous_link)&&
                (hub!=(*this))&&
                (!hub.lead_to(*this))&&
                (!this->lead_to(hub))&&
                (!contains(get_node_of_whole_figure().first_hubs(), hub))
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
