#include "./Iterator_BFS.h"

#include "core/Bend/Figure_bend/Figure_bend.h"
#include "core/Bend/Figure_bend/figure_bend_data.h"

namespace core {

Node::iterator_BFS::iterator_BFS():
    figure_bend()
{

}

Node::iterator_BFS::iterator_BFS(Node in_node)
{
    for(Figure_bend figure: in_node.get_arr_figure_bends()) {
        queue_figure.push(figure);
    }
    if (queue_figure.size()) {
        set_to_figure(queue_figure.front());
        queue_figure.pop();
    }

}

Node::iterator_BFS::iterator_BFS(Figure_bend in_figure_bend)
{
    set_to_figure(in_figure_bend);
}

void Node::iterator_BFS::set_to_figure(Figure_bend in_figure) {
    figure_bend = in_figure;
    for(Figure_bend next_figure: figure_bend.get_arr_next_figures()) {
        queue_figure.push(next_figure);
    }
}


Node::iterator_BFS Node::iterator_BFS::operator++(int) {
    (*this)++;

}


Node::iterator_BFS& Node::iterator_BFS::operator++()
{
    if (queue_figure.size() > 0) {
        set_to_figure(queue_figure.front());
        queue_figure.pop();
    } else {
        figure_bend = Figure_bend::new_empty();
    }

    return *this;

}

bool Node::iterator_BFS::is_end()
{
    return figure_bend.is_empty();
}


}
