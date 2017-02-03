#include "./Iterator_BFS.h"

#include "core/Network/Node/Hub/Hub.h"
#include "core/Network/Node/Hub/Hub_data.h"

namespace core {

Node::iterator_BFS::iterator_BFS():
    hub()
{

}

Node::iterator_BFS::iterator_BFS(Node in_node)
{
    for(Hub figure: in_node.get_arr_hubs()) {
        queue_hub.push(figure);
    }
    if (queue_hub.size()) {
        continue_with_hub(queue_hub.front());
        queue_hub.pop();
    }

}

Node::iterator_BFS::iterator_BFS(Hub in_figure_bend)
{
    continue_with_hub(in_figure_bend);
}

void Node::iterator_BFS::continue_with_hub(Hub in_figure) {
    hub = in_figure;
    for(Hub next_figure: hub.get_arr_next_figures()) {
        queue_hub.push(next_figure);
    }
}


Node::iterator_BFS Node::iterator_BFS::operator++(int) {
    (*this)++;

}


Node::iterator_BFS& Node::iterator_BFS::operator++()
{
    if (queue_hub.size() > 0) {
        continue_with_hub(queue_hub.front());
        queue_hub.pop();
    } else {
        hub = Hub::new_empty();
    }

    return *this;

}

bool Node::iterator_BFS::is_end()
{
    return hub.is_empty();
}


}
