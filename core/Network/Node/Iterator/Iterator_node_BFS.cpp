#include "./Iterator_node_BFS.h"

#include "core/Network/Network.h"
#include "core/Network/Node/Hub/Hub.h"
#include "core/Network/Node/Hub/Hub_data.h"

namespace core {

iterator_node_BFS::iterator_node_BFS():
    node{Node::get_empty()}
{

}

iterator_node_BFS::iterator_node_BFS(Network& network)
{
    for(Node node: network.input) {
        enqueue_for_iteration(node);
    }
    for(Node node: network.output) {
        enqueue_for_iteration(node);
    }
    if (queue_node.size()) {
        continue_with_node(queue_node.front());
        queue_node.pop();
    }
}


iterator_node_BFS::iterator_node_BFS(Node in_node)
{
    continue_with_node(in_node);
}

void iterator_node_BFS::go_to_high_nodes(Network &network)
{
    for(Node node: network.input) {
        enqueue_higher_nodes_of(node);
    }
    for(Node node: network.output) {
        enqueue_higher_nodes_of(node);
    }
    if (queue_node.size()) {
        continue_with_node(queue_node.front());
        queue_node.pop();
    }
}


void iterator_node_BFS::continue_with_node(Node in_node) {
    node = in_node;
    enqueue_higher_nodes_of(in_node);
}

void iterator_node_BFS::enqueue_higher_nodes_of(Node in_node) {
    for(Bend bend: in_node.bends()) {
        for (Hub hub: bend.hubs()) {
            enqueue_for_iteration(hub.get_node_of_whole_figure());
        }
    }
}

void iterator_node_BFS::enqueue_for_iteration(Node in_node)
{
    queue_node.push(in_node);
    ordered_nodes.emplace(in_node);
}



iterator_node_BFS iterator_node_BFS::operator++(int) {
    auto temp = *this;  
    ++*this;  
    return temp; 

}



iterator_node_BFS& iterator_node_BFS::operator++()
{
    if (queue_node.size() > 0) {
        continue_with_node(queue_node.front());
        queue_node.pop();
    } else {
        node = Node::get_empty();
    }

    return *this;

}

bool iterator_node_BFS::is_end()
{
    return node.is_empty();
}


}
