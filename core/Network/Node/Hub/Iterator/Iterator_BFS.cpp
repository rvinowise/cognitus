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
    for(Hub hub: in_node.first_hubs()) {
        enqueue_for_iteration(hub);
    }
    if (queue_hub.size()) {
        continue_with_hub(queue_hub.front());
        queue_hub.pop();
    }

}

iterator_hub_BFS::iterator_hub_BFS(Hub in_hub)
{
    continue_with_hub(in_hub);
}

void iterator_hub_BFS::continue_with_hub(Hub in_hub) {
    hub = in_hub;
    for(Hub next_hub: hub.get_arr_next_hubs()) {
        if (!ordered_hubs.count(next_hub)) {
            enqueue_for_iteration(next_hub);
        }
    }
}

void iterator_hub_BFS::enqueue_for_iteration(Hub in_hub)
{
    queue_hub.push(in_hub);
    ordered_hubs.emplace(in_hub);
}


iterator_hub_BFS iterator_hub_BFS::operator++(int) {
    auto temp = *this;  
    ++*this;  
    return temp;
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
