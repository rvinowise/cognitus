#include "./Iterator_node_BFS.h"

#include "core/Network/Node/Hub/Hub.h"
#include "core/Network/Node/Hub/Hub_data.h"

namespace core {

Network::iterator_node_BFS::iterator_node_BFS():
    node()
{

}

Network::iterator_node_BFS::iterator_node_BFS(Network& network)
{
    for(Node node: network.input) {
        queue_node.push(node);
    }
    for(Node node: network.output) {
        queue_node.push(node);
    }
    if (queue_node.size()) {
        continue_with_node(queue_node.front());
        queue_node.pop();
    }
}


Network::iterator_node_BFS::iterator_node_BFS(Node in_node)
{
    continue_with_node(in_node);
}

void Network::iterator_node_BFS::continue_with_node(Node in_node) {
    node = in_node;
    for(Bend bend: node.bends()) {
        for (Hub hub: bend.hubs()) {
            queue_node.push(hub.get_node_of_whole_figure());
        }
    }
}


Network::iterator_node_BFS Network::iterator_node_BFS::operator++(int) {
    (*this)++;

}


Network::iterator_node_BFS& Network::iterator_node_BFS::operator++()
{
    if (queue_node.size() > 0) {
        continue_with_node(queue_node.front());
        queue_node.pop();
    } else {
        node = Node::new_empty();
    }

    return *this;

}

bool Network::iterator_node_BFS::is_end()
{
    return node.is_empty();
}


}
