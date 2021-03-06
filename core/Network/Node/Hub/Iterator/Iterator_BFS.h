#pragma once

#include <iterator>
#include <queue>
#include <unordered_set>

#include "core/Network/Node/Node.h"
#include "core/Network/Node/Hub/Hub.h"

namespace core {

class iterator_hub_BFS// : public std::iterator<std::forward_iterator_tag, Figure_bend*>
{
public:
    iterator_hub_BFS();
    iterator_hub_BFS(Hub in_figure_bend);
    iterator_hub_BFS(Node in_node);
    iterator_hub_BFS(const iterator_hub_BFS& other):
        hub(other.hub), queue_hub(other.queue_hub)
    {

    }
    void continue_with_hub(Hub in_hub);
    bool is_end();

    iterator_hub_BFS& operator++();
    iterator_hub_BFS operator++(int);
    Hub operator*() { return hub; }
    Hub operator->() { return hub; }
    bool operator==(const iterator_hub_BFS& other) { return hub == other.hub; }
    bool operator!=(const iterator_hub_BFS& other) { return hub != other.hub; }
    iterator_hub_BFS& operator=(const iterator_hub_BFS& other) {
        hub = other.hub;
        queue_hub = other.queue_hub;
        return *this;
    }

private:
    void enqueue_for_iteration(Hub in_hub);

    core::Hub hub;
    std::queue<Hub> queue_hub;
    std::unordered_set<Hub> ordered_hubs;
};






}
