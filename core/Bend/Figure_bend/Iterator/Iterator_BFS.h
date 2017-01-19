#pragma once

#include <iterator>
#include <queue>

#include "core/Node/Node.h"
#include "core/Bend/Figure_bend/Figure_bend.h"
#include "core/Bend/Figure_bend/figure_bend_data.h"

namespace core {

class Node::iterator_BFS// : public std::iterator<std::forward_iterator_tag, Figure_bend*>
{
public:
    iterator_BFS();
    iterator_BFS(Figure_bend in_figure_bend);
    iterator_BFS(Node in_node);
    iterator_BFS(const iterator_BFS& other):
        figure_bend(other.figure_bend), queue_figure(other.queue_figure)
    {

    }
    void set_to_figure(Figure_bend in_figure);
    bool is_end();

    iterator_BFS& operator++();
    iterator_BFS operator++(int);
    Figure_bend operator*() { return figure_bend; }
    Figure_bend operator->() { return figure_bend; }
    bool operator==(const iterator_BFS& other) { return figure_bend == other.figure_bend; }
    bool operator!=(const iterator_BFS& other) { return figure_bend != other.figure_bend; }
    iterator_BFS& operator=(const iterator_BFS& other) {
        figure_bend = other.figure_bend;
        queue_figure = other.queue_figure;
        return *this;
    }

private:
    Figure_bend figure_bend;
    std::queue<Figure_bend> queue_figure;
};






}
