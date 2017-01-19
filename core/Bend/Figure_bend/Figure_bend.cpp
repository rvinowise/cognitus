#include "Figure_bend.h"

#include "figure_bend_data.h"

#include "core/Node/Node_data.h"
#include "core/Bend/Figure_bend/Iterator/Iterator_BFS.h"

namespace core {


Figure_bend_data::Figure_bend_data():
    Acquiring_handles()
{
}

Figure_bend_data::Figure_bend_data(Node in_figure_node):
    figure_node(in_figure_node), Acquiring_handles()
{

}

Figure_bend_data::Figure_bend_data(Node_data in_figure_node_data):
    figure_node(in_figure_node_data), Acquiring_handles()
{

}


Figure_bend::Figure_bend()
{
    data = nullptr;
}

Figure_bend::Figure_bend(Node in_figure_node)
{
    data = new Figure_bend_data(in_figure_node);
}

Figure_bend::Figure_bend(Node_data in_figure_node_data)
{
    data = new Figure_bend_data(in_figure_node_data);
}

Figure_bend::Figure_bend(const Figure_bend &other)
{
    data = other.data;
    if (data) {
        data->connect_a_handle();
    }
}

Figure_bend::~Figure_bend()
{
    if (data) {
        data->disconnect_a_handle();
    }
}

Figure_bend Figure_bend::new_empty()
{
    Figure_bend figure;
    return figure;
}

bool Figure_bend::is_empty()
{
    return data==nullptr;
}

bool Figure_bend::operator==(const Figure_bend &other)
{
    return data == other.data;
}
bool Figure_bend::operator!=(const Figure_bend &other)
{
    return data != other.data;
}

Figure_bend &Figure_bend::operator=(const Figure_bend &other)
{
    data = other.data;
    if (data) {
        data->connect_a_handle();
    }
    return *this;
}

std::size_t Figure_bend::get_prev_links_qty() const
{
    return data->prev_bends.size();
}
std::size_t Figure_bend::get_next_links_qty() const
{
    return data->next_bends.size();
}

std::vector<Figure_bend>& Figure_bend::get_arr_next_figures()
{
    return data->next_bends;
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

void Figure_bend::push_next_bend(Figure_bend in_figure)
{
    data->next_bends.push_back(in_figure);
}

std::vector<Bend>& Figure_bend::get_arr_free_bends()
{
    return data->free_bends;
}

#ifdef debug_mode
void Figure_bend::letdown_new_bends_to_node(std::size_t qty, Node node)
{
    for (std::size_t i_bend=0; i_bend<qty; i_bend++) {
        data->free_bends.push_back(Bend(node));
    }
}

std::vector<Figure_bend> Figure_bend::get_arr_not_linked_figures(std::vector<Figure_bend> figures)
{
    std::vector<Figure_bend> result;
    for (Figure_bend figure: figures) {
        if (
                (figure!=(*this))&&
                (!figure.lead_to(*this))&&
                (!this->lead_to(figure))
            ) {
            result.push_back(figure);
        }
    }
    return result;
}

bool Figure_bend::lead_to(Figure_bend other)
{
    for (
         Node::iterator_BFS iter(*this);
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
