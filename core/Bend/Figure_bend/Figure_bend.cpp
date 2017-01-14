#include "Figure_bend.h"

#include "figure_bend_data.h"

namespace core {


Figure_bend_data::Figure_bend_data()
{
}


Figure_bend::Figure_bend()
{

}

Figure_bend::~Figure_bend()
{

}

std::size_t Figure_bend::get_prev_links_qty() const
{
    return data->prev_bends.size();
}
std::size_t Figure_bend::get_next_links_qty() const
{
    return data->next_bends.size();
}


Node& Figure_bend::get_node_of_whole_figure()
{
    return data->figure_node;
}

bool Figure_bend::is_this_last_bend_in_chain() const {
    return data->next_bends.empty();
}

Figure_bend Figure_bend::add_next_bend()
{
    data->next_bends.push_back(Figure_bend());
    return data->next_bends.back();
}



}
