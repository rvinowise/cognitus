#pragma once

#include <iterator>
#include <queue>

#include "core/Network/Node/Node.h"
#include "core/Network/Node/Hub/Hub.h"
#include "core/Network/Node/Hub/Hub_data.h"

namespace core {

class Node::iterator_BFS// : public std::iterator<std::forward_iterator_tag, Figure_bend*>
{
public:
    iterator_BFS();
    iterator_BFS(Hub in_figure_bend);
    iterator_BFS(Node in_node);
    iterator_BFS(const iterator_BFS& other):
        hub(other.hub), queue_hub(other.queue_hub)
    {

    }
    void continue_with_hub(Hub in_figure);
    bool is_end();

    iterator_BFS& operator++();
    iterator_BFS operator++(int);
    Hub operator*() { return hub; }
    Hub operator->() { return hub; }
    bool operator==(const iterator_BFS& other) { return hub == other.hub; }
    bool operator!=(const iterator_BFS& other) { return hub != other.hub; }
    iterator_BFS& operator=(const iterator_BFS& other) {
        hub = other.hub;
        queue_hub = other.queue_hub;
        return *this;
    }

private:
    Hub hub;
    std::queue<Hub> queue_hub;
};






}
