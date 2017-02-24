#include "Iterator_bend_BFS.h"

#include "core/Network/Node/Bend/Bend.h"

namespace core {

Iterator_bend_BFS::Iterator_bend_BFS():
    bend{Bend()}
{
    
}
Iterator_bend_BFS::Iterator_bend_BFS(Bend in_bend):
    bend{in_bend},
    direction{Direction::not_initialized}
{
    
}

void Iterator_bend_BFS::continue_backward_with_bend(Bend in_bend)
{
    bend = in_bend;
    enqueue_prev_bends_of(in_bend);
}
void Iterator_bend_BFS::continue_forward_with_bend(Bend in_bend)
{
    bend = in_bend;
    enqueue_next_bends_of(in_bend);
}


inline bool Iterator_bend_BFS::is_not_enqueued_already(Bend in_bend) {
    return !ordered_bends.count(in_bend);
}

void Iterator_bend_BFS::enqueue_prev_bends_of(Bend in_bend) {
    for(Bend bend: in_bend.prev_bends()) {
        if (
                (is_not_enqueued_already(bend))&&
                (
                    (final_bend.is_empty())||
                    (
                        (!bend.executed_before_this(final_bend))&&
                        (bend != final_bend)
                     )
                 )
            ){
            enqueue_for_iteration(bend);
        }
    }
}
void Iterator_bend_BFS::enqueue_next_bends_of(Bend in_bend) {
    for(Bend bend: in_bend.next_bends()) {
        if (
                (is_not_enqueued_already(bend))&&
                (
                    (final_bend.is_empty())||
                    (
                        (!bend.executed_after_this(final_bend))&&
                        (bend != final_bend)
                     )
                 )
             ){
            enqueue_for_iteration(bend);
        }
    }
}


void Iterator_bend_BFS::enqueue_for_iteration(Bend in_bend)
{
    queue_bend.push(in_bend);
    ordered_bends.emplace(in_bend);

}

void Iterator_bend_BFS::clear_memory_state()
{
    queue_bend = std::queue<Bend>();
    ordered_bends.clear();
}


void Iterator_bend_BFS::end_loop_after_this_bend(Bend in_final_bend)
{
    final_bend = in_final_bend;
}


Iterator_bend_BFS Iterator_bend_BFS::operator++(int) {
    auto temp = *this;  
    ++*this;  
    return temp;
}

Iterator_bend_BFS& Iterator_bend_BFS::operator++()
{
    if (direction!=Direction::forward) {
        if (direction==Direction::backward) {
            clear_memory_state();
        }
        direction = Direction::forward;
        enqueue_next_bends_of(bend);
    }
    if (queue_bend.size() > 0) {
        continue_forward_with_bend(queue_bend.front());
        queue_bend.pop();
    } else {
        bend = Bend();
    }

    return *this;
}


Iterator_bend_BFS Iterator_bend_BFS::operator--(int) {
    auto temp = *this;  
    --*this;  
    return temp;
}

Iterator_bend_BFS& Iterator_bend_BFS::operator--()
{
    if (direction!=Direction::backward) {
        if (direction==Direction::forward) {
            clear_memory_state();
        }
        direction = Direction::backward;
        enqueue_prev_bends_of(bend);
    } 
    if (queue_bend.size() > 0) {
        continue_backward_with_bend(queue_bend.front());
        queue_bend.pop();
    } else {
        bend = Bend();
    }

    return *this;

}

bool Iterator_bend_BFS::is_end()
{
    return bend.is_empty();
}

Iterator_bend_BFS Iterator_bend_BFS::end()
{
    return Iterator_bend_BFS();
}


}
