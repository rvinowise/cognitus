#include "Node.h"
#include "Node_data.h"

#include <utility>

#include "core/Network/Network.h"
#include "core/Network/Node/Hub/Iterator/Iterator_BFS.h"

#ifdef debug_mode
#include "core/test/randomFunc.h"
#endif

namespace core {

Node_data::Node_data()
{
}


Node::Node():
    data{nullptr}
{

}

Node::Node(Circuit inCircuit)
{
#ifdef rendering_mode
    render::Node::create_data();
#endif
    data = new Node_data();
    incorporate_circuit_to_this_node(inCircuit);
}

Node::Node(const Node &other)
#ifdef rendering_mode
    :render::Node(other)
#endif
{
    data = other.data;
}

Node::Node(Node &&other)
#ifdef rendering_mode
    :render::Node(std::move(other))
#endif
{
    data = other.data;
    other.data = nullptr;
}

Node::~Node()
{

}

void Node::create_data()
{
    data = new Node_data();
#ifdef rendering_mode
    render::Node::create_data();
#endif
}

Node Node::get_empty()
{
    Node node;
    return node;
}
bool Node::is_empty() const
{
    return data==nullptr;
}

void Node::deallocate_with_all_connected_entities_upward()
{
    for (auto bend: this->data->bends) {
        //bend.
    }
    delete data;
}

Node& Node::operator=(const Node &other)
{
#ifdef rendering_mode
    render::Node::data = other.render::Node::data;
#endif
    data = other.data;
    return *this;
}

bool Node::operator==(const Node &other) const
{
    return data==other.data;
}

bool Node::operator!=(const Node &other) const
{
    return data!=other.data;
}

bool Node::operator<(const Node &other) const
{
    return reinterpret_cast<std::size_t>(data) <
            reinterpret_cast<std::size_t>(other.data);
}







bool there_are_other_bends_inside_this_line(Sequence_pair inLine) {
    return inLine.is_has_noise_bends_inside();
}

void delete_initial_chain_which_is_redundant_now(Sequence_pair inChain) {
    inChain.start().remove();
    inChain.end().remove();
}

void Node::carefully_preserve_initial_chain_because_of_its_context(
        Sequence_pair inLine,
        Hub first_hub,
        Hub second_hub) {
    inLine.start().attach_to_hub(first_hub);
    inLine.end().attach_to_hub(second_hub);
}

void Node::incorporate_circuit_to_this_node(Circuit inCircuit)
{
    if (data->bends.size() > 0) {
        throw("incorporating circuit is only for _new_ Nodes");
    }
    if (!inCircuit.is_complete()) {
        throw("trying to incorporate an _incomplete_ Circuit to Node");
    }
    Bend firstHigherBend = add_bend_according_to_line(
                inCircuit.get_first_line());
    Bend secondHigherBend = add_bend_according_to_line(
                inCircuit.get_second_line());

    Hub first_hub = this->add_hub();
    first_hub.set_name(inCircuit.get_first_line().start().name());
    Hub second_hub = first_hub.add_next_hub();
    second_hub.set_name(inCircuit.get_first_line().end().name());
    
    this->set_name(QString("%1%2").arg(first_hub.name()).arg(second_hub.name()));

    //if (there_are_other_bends_inside_this_line(inCircuit.get_first_line())) {
        carefully_preserve_initial_chain_because_of_its_context(
                    inCircuit.get_first_line(),
                    first_hub, second_hub);
    //} else {
    //    delete_initial_chain_which_is_redundant_now(inCircuit.get_first_line());
    //}
}

Bend Node::add_bend_according_to_line(Sequence_pair in_line)
{
    Bend bend = add_bend();
    bend.incorporate_line_to_this_bend(in_line);
    
    return bend;
}

Bend Node::fire()
{
    return add_bend(Network::this_moment());
}



Bend Node::add_bend()
{
    Bend new_bend(*this, bends().size());
    bends().push_back(new_bend);
    return new_bend;
}

Bend Node::add_bend(Activation_interval interval)
{
    Bend new_bend(*this, bends().size());
    new_bend.set_interval(interval);
    bends().push_back(new_bend);
    return new_bend;
}


std::vector<Hub>& Node::first_hubs()
{
    return data->hubs;
}

const std::vector<Hub>& Node::first_hubs() const
{
    return data->hubs;
}

Hub Node::add_hub()
{
    data->hubs.push_back(Hub(*this));
    return data->hubs.back();
}

std::vector<Bend>& Node::bends()
{
    return data->bends;
}

const std::vector<Bend>& Node::bends() const
{
    return data->bends;
}

iterator_hub_BFS Node::begin()
{
    return iterator_hub_BFS(*this);
}
iterator_hub_BFS Node::end()
{
    return iterator_hub_BFS();
}


#ifdef debug_mode

bool Node::has_it_as_progeny(Node in_node)
{
    for (Hub figure: *this) {
        for (Bend child_bend: figure.get_arr_free_bends()) {
            Node child_node = child_bend.get_master_node();
            if (child_node == in_node) {
                return true;
            }
            return child_node.has_it_as_progeny(in_node);
        }
    }
    return false;
}

bool Node::is_progeny_of(Node node)
{
    return node.has_it_as_progeny(*this);
}

void Node::generate_random_empty_figure(std::size_t figure_size)
{
    unsigned int figure_wideness = 3;
    std::vector<Hub> hubs(figure_size);
    for (size_t i_hub=0; i_hub<figure_size; i_hub++) {
        hubs[i_hub] = Hub(*this);
    }
    for (size_t i_hub=0; i_hub<figure_wideness; i_hub++) {
        this->first_hubs().push_back(hubs[i_hub]);
    }

    for (Hub hub: hubs) {
        std::vector<Hub> potential_next_hubs=
                hub.get_hubs_possible_for_linking(hubs);
        size_t figure_picking_step = potential_next_hubs.size()-2;
        for (
             size_t i_potential_next = 0;
             i_potential_next < potential_next_hubs.size();
             ++i_potential_next += test::random(figure_picking_step)
             ) {
            hub.push_next_hub(potential_next_hubs[i_potential_next]);
        }
    }
}
#endif


}
