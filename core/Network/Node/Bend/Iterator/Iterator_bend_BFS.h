#pragma once

#include <queue>
#include <unordered_set>

#include "core/Network/Node/Bend/Bend.h"

namespace core {



class Iterator_bend_BFS
{
public:
    Iterator_bend_BFS();
    Iterator_bend_BFS(Bend in_bend);
    Iterator_bend_BFS(const Iterator_bend_BFS& other):
        bend(other.bend), queue_bend(other.queue_bend){}
    
    bool is_end();
    
    Iterator_bend_BFS& operator++();
    Iterator_bend_BFS operator++(int);
    Iterator_bend_BFS& operator--();
    Iterator_bend_BFS operator--(int);
    Bend operator*() { return bend; }
    Bend operator->() { return bend; }
    bool operator==(const Iterator_bend_BFS& other) { return bend == other.bend; }
    bool operator!=(const Iterator_bend_BFS& other) { return bend != other.bend; }
    
private:
    enum class Direction
    {
        backward, forward, not_initialized
    } direction;
    
    void enqueue_for_iteration(Bend in_bend);
    void clear_memory_state();
    void continue_forward_with_bend(Bend in_bend);
    void continue_backward_with_bend(Bend in_bend);
    void enqueue_prev_bends_of(Bend in_bend);
    void enqueue_next_bends_of(Bend in_bend);

    Bend bend;
    std::queue<Bend> queue_bend;
    std::unordered_set<Bend> ordered_bends;
};


}
