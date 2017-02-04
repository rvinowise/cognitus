#include "./Iterator_BFS.h"

#include "core/Network/Node/Hub/Hub.h"
#include "core/Network/Node/Hub/Hub_data.h"

namespace core {

iterator_hub_BFS::iterator_hub_BFS():
    hub()
{

}

iterator_hub_BFS::iterator_hub_BFS(Node in_node)
{
    for(Hub figure: in_node.first_hubs()) {
        queue_hub.push(figure);
    }
    if (queue_hub.size()) {
        continue_with_hub(queue_hub.front());
        queue_hub.pop();
    }

}

iterator_hub_BFS::iterator_hub_BFS(Hub in_figure_bend)
{
    continue_with_hub(in_figure_bend);
}

void iterator_hub_BFS::continue_with_hub(Hub in_figure) {
    hub = in_figure;
    for(Hub next_figure: hub.get_arr_next_hubs()) {
        queue_hub.push(next_figure);
    }
}


iterator_hub_BFS iterator_hub_BFS::operator++(int) {
    (*this)++;

}


iterator_hub_BFS& iterator_hub_BFS::operator++()
{
    if (queue_hub.size() > 0) {
        continue_with_hub(queue_hub.front());
        queue_hub.pop();
    } else {
        hub = Hub::new_empty();
    }

    return *this;

}

bool iterator_hub_BFS::is_end()
{
    return hub.is_empty();
}


}
