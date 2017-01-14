#pragma once


#include <vector>
#include <set>
#include <memory>

#include "core/Bend/Link/Linked.h"
#include "core/auxiliary/Acquiring_handles/Acquiring_handles.h"

namespace core {

class Bend_data;
class Node;
class Figure_bend;

class Bend: public Linked
{
public:
    Bend();
    Bend(Node &masterNode);
    Bend(const Bend& other);
    Bend(Bend&& other);
    ~Bend();
    Bend& operator=(const Bend& other);
    bool operator==(const Bend& other) const;
    bool operator!=(const Bend& other) const;


    bool is_empty() const;

    Node& get_master_node();

    std::size_t get_prev_links_qty() const;
    std::size_t get_next_links_qty() const;
    Bend get_prev_bend(std::size_t index) const;
    Bend get_next_bend(std::size_t index) const;

    const std::vector<Bend>& get_array_of_prev_bends() const;
    const std::vector<Bend>& get_array_of_next_bends() const;

    std::size_t get_higher_nodes_qty() const;
    Node get_higher_node(std::size_t index) const;
    std::vector<Node> get_common_higher_nodes_with(Bend otherBend);


    void append_to_higher_node(Node& inNode);
    void copy_prev_bends_from(Bend otherBend);
    void copy_next_bends_from(Bend otherBend);
    void attach_to_bend_of_figure(Figure_bend figureBend);
    Bend add_next_bend();
    void connect_to(Bend& toBend);

    void deallocate_all_connected_entities_upward();
    void remove();

protected:
    void erase_next_bend(std::size_t index);
    void erase_prev_bend(std::size_t index);

private:
    Bend_data* data;

};


}
