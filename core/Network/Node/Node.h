#pragma once

#include <vector>

#ifdef render_mode
#include "interface/drawable_units/draw_Node.h"
#endif

namespace core {

class Sequence_pair;
class Circuit;
class Bend;
class Hub;
class Node_data;
class iterator_hub_BFS;

class Node
#ifdef render_mode
        :public render::Node
#endif
{
friend class InterfaceNode;
friend class render::Node;
friend struct std::hash<core::Node>;
public:
    Node();
    Node(const Node& other);
    Node(Node&& other);
    Node(Circuit inCircuit);
    ~Node();
    void create_data();
    static Node get_empty();
    bool is_empty()const;

    void deallocate_with_all_connected_entities_upward();

    Node& operator=(const Node& other);
    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;
    bool operator<(const Node& other) const;

    void incorporate_circuit_to_this_node(Circuit inCircuit);

    virtual Bend fire();

    bool isLowest();
    Bend add_bend();
    void append_bend(const Bend& bend);

    Hub add_hub();


    iterator_hub_BFS begin() override;
    iterator_hub_BFS end() override;
    typedef Hub value_type;

    std::vector<core::Hub>& first_hubs();
    const std::vector<Hub>& first_hubs()const;
    std::vector<core::Bend>& bends();
    const std::vector<core::Bend>& bends()const;

#ifdef debug_mode
   bool has_it_as_progeny(Node node);
   bool is_progeny_of(Node node);
   void generate_random_empty_figure(std::size_t figure_size);
#endif

private:
   void carefully_preserve_initial_chain_because_of_its_context(
           Sequence_pair inLine, Hub first_chain_bend, Hub second_chain_bend);


    Node_data* data; 
};


}

namespace std {
  template <> struct hash<core::Node>
  {
    size_t operator()(const core::Node& node) const
    {
      return hash<std::size_t>()(
                  reinterpret_cast<std::size_t>(node.data)
                  );
    }
  };
}
