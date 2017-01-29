#include "Node.h"
#include "Node_data.h"

#include "core/Network/Network.h"
#include "core/Bend/Figure_bend/Iterator/Iterator_BFS.h"

#ifdef debug_mode
#include "core/test/randomFunc.h"
#endif

namespace core {

Node_data::Node_data():
    Acquiring_handles()
{
}


Node::Node()
{
    data = new Node_data;

}

Node::Node(Node_data& in_node_data)
{
    data = &in_node_data;
    if (data) {
        data->connect_a_handle();
    }
}

Node::Node(const Node &other)
{
    data = other.data;
    if(data) {
        data->connect_a_handle();
    }
}

Node::Node(Node &&other)
{
    data = other.data;
    other.data = nullptr;
}

Node::~Node()
{
    if (data) {
        data->disconnect_a_handle();
    }
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
    inLine.get_start().attach_to_figure(first_chain_bend);
    inLine.get_end().attach_to_figure(second_chain_bend);
}

void Node::incorporate_circuit_to_this_node(Circuit inCircuit)
{
    if (data->bends.size() > 0) {
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

    Figure_bend first_figure_bend = this->add_figure_bend();
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
    data->bends.push_back(newBend);
    global_network->save_new_activated_bend(newBend);
}



Bend Node::add_bend()
{
    data->bends.push_back(Bend(*this));
    return data->bends.back();
}

void Node::append_bend(const Bend& bend)
{
    data->bends.push_back(bend);
}

std::vector<Figure_bend>& Node::get_arr_figure_bends()
{
    return data->figure_bends;
}

Figure_bend Node::add_figure_bend()
{
    data->figure_bends.push_back(Figure_bend(*this));
    return data->figure_bends.back();
}

std::vector<Bend>& Node::bends()
{
    return data->bends;
}

Node::iterator_BFS Node::begin()
{
    return iterator_BFS(*this);
}
Node::iterator_BFS Node::end()
{
    return iterator_BFS();
}

#ifdef debug_mode

//using test::random;

bool Node::has_it_as_progeny(Node in_node)
{
    for (Figure_bend figure: *this) {
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

    std::vector<Figure_bend> figures(figure_size);
    for (size_t i_figure=0; i_figure<figure_size; i_figure++) {
        figures[i_figure] = Figure_bend(*this);
    }
    for (Figure_bend figure: figures) {
        std::vector<Figure_bend> potential_next_figures=
                figure.get_arr_not_linked_figures(figures);
        unsigned int figure_picking_step = potential_next_figures.size()-2;
        for (
             size_t i_potential_next = 0;
             i_potential_next < potential_next_figures.size();
             i_potential_next += (1+test::random(figure_picking_step))
             ) {
            figure.push_next_bend(potential_next_figures[i_potential_next]);
        }
    }
}
#endif


}
