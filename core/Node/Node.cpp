#include "Node.h"
#include "Node_data.h"

#include "core/Network/Network.h"


namespace core {

Node_data::Node_data()
{
}


Node::Node()
{
    data = new Node_data;

}

Node::Node(const Node &other)
{
    data = other.data;
    data->connect_a_handle();
}

Node::Node(Node &&other)
{
    data = other.data;
}

Node::~Node()
{
    data->disconnect_a_handle();
}

void Node::deallocate_with_all_connected_entities_upward()
{
    for (auto bend: this->data->bend) {
        //bend.
    }
    delete data;
}

Node& Node::operator=(const Node &other)
{
    data = other.data;
    return *this;
}

bool Node::operator==(const Node &other) const
{
    return data==other.data;
}



Node::Node(Circuit inCircuit)
{
    data = new Node_data;
    incorporate_circuit_to_this_node(inCircuit);
}


bool there_are_other_bends_inside_this_line(LineOfCircuit inLine) {
    return inLine.is_has_noise_bends_inside();
}

void delete_initial_chain_which_is_redundant_now(LineOfCircuit inChain) {
    inChain.get_start().remove();
    inChain.get_end().remove();
}

void Node::carefully_preserve_initial_chain_because_of_its_context(
        LineOfCircuit inLine,
        Figure_bend first_chain_bend,
        Figure_bend second_chain_bend) {
    inLine.get_start().attach_to_bend_of_figure(first_chain_bend);
    inLine.get_end().attach_to_bend_of_figure(second_chain_bend);
}

void Node::incorporate_circuit_to_this_node(Circuit inCircuit)
{
    if (data->bend.size() > 0) {
        throw("incorporating circuit is only for _new_ Nodes");
    }
    if (!inCircuit.is_complete()) {
        throw("trying to incorporate an _incomplete_ Circuit to Node");
    }
    Bend firstHigherBend = this->add_bend();
    firstHigherBend.copy_prev_bends_from(inCircuit.getFirstStartBend());
    firstHigherBend.copy_next_bends_from(inCircuit.getFirstEndBend());
    Bend secondHigherBend = this->add_bend();
    secondHigherBend.copy_prev_bends_from(inCircuit.getSecondStartBend());
    secondHigherBend.copy_next_bends_from(inCircuit.getSecondEndBend());

    Figure_bend first_figure_bend = this->get_lower_chain_bend().add_next_bend();
    Figure_bend second_figure_bend = first_figure_bend.add_next_bend();

    if (there_are_other_bends_inside_this_line(inCircuit.get_first_line())) {
        carefully_preserve_initial_chain_because_of_its_context(
                    inCircuit.get_first_line(),
                    first_figure_bend, second_figure_bend);
    } else {
        delete_initial_chain_which_is_redundant_now(inCircuit.get_first_line());
    }
}

void Node::fire()
{
    add_new_bend_as_active();
}



void Node::add_new_bend_as_active() {
    Bend newBend(*this);
    data->bend.push_back(newBend);
    global_network->save_new_activated_bend(newBend);
}



Bend Node::add_bend()
{
    data->bend.push_back(Bend(*this));
    return data->bend.back();
}

Figure_bend Node::get_lower_chain_bend()
{
    return data->lower_chain_bend;
}


}
