#pragma once

#include <iterator>
#include <queue>
#include <unordered_set>

#include "core/Network/Node/Node.h"
#include "core/Network/Node/Node_data.h"

namespace core {

class Network;

class iterator_node_BFS
{
public:
    iterator_node_BFS();
    iterator_node_BFS(Network& network);
    iterator_node_BFS(Node in_node);
    iterator_node_BFS(const iterator_node_BFS& other):
        node(other.node), queue_node(other.queue_node)
    {

    }
    void go_to_high_nodes(Network& network);

    void continue_with_node(Node in_node);
    void enqueue_higher_nodes_of(Node in_node);
    bool is_end();

    iterator_node_BFS& operator++();
    iterator_node_BFS operator++(int);
    Node operator*() { return node; }
    Node operator->() { return node; }
    bool operator==(const iterator_node_BFS& other) { return node == other.node; }
    bool operator!=(const iterator_node_BFS& other) { return node != other.node; }
    iterator_node_BFS& operator=(const iterator_node_BFS& other) {
        node = other.node;
        queue_node = other.queue_node;
        return *this;
    }

private:
    void enqueue_for_iteration(Node in_node);

    Node node;
    std::queue<Node> queue_node;
    std::unordered_set<Node> ordered_nodes;
};






}
