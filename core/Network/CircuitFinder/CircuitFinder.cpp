#include "CircuitFinder.h"

#include "core/Network/Node/Node.h"
#include "interface/algorithms.h"
#include "core/Network/Node/Bend/Iterator/Iterator_bend_BFS.h"

namespace core {

using std::size_t;

CircuitFinder::CircuitFinder()
{

}

void fill_map_of_prev_nodes_and_bends(std::map<Node, Bend>& prev_nodes, Bend last_end_bend)
{
    Bend prev_brother_bend = last_end_bend.get_prev_brother_bend();
    Iterator_bend_BFS i_prev_bend(last_end_bend);
    i_prev_bend.end_loop_after_this_bend(prev_brother_bend);
    for (--i_prev_bend;
         i_prev_bend != Iterator_bend_BFS::end();
         --i_prev_bend) {
        Bend prev_bend = *i_prev_bend;
        
        prev_nodes[prev_bend.get_master_node()] = prev_bend;
      
        /*if (++current_search_deepening == search_area) {
            break;
        }*/
    }
}

Circuit find_last_circuit_with_this(std::map<Node, Bend> prev_nodes, Bend last_end_bend)
{
    Node end_master_node = last_end_bend.get_master_node();
    for (std::size_t i_brother_bend = last_end_bend.get_index_in_master_node()-1;
         i_brother_bend != std::numeric_limits<std::size_t>::max();
         --i_brother_bend
         ) {
        Bend brother_bend = end_master_node.bends()[i_brother_bend];
        
        Iterator_bend_BFS i_prev_brother_bend(brother_bend);
        i_prev_brother_bend.end_loop_after_this_bend(
                    brother_bend.get_prev_brother_bend());
        for (--i_prev_brother_bend;
             i_prev_brother_bend != Iterator_bend_BFS::end();
             --i_prev_brother_bend) {
            Bend prev_brother_bend = *i_prev_brother_bend;
            Node prev_brother_node = prev_brother_bend.get_master_node();
            if (prev_nodes.count(prev_brother_node)) {
                Sequence_pair last_line{prev_nodes[prev_brother_node], last_end_bend};
                Sequence_pair prev_line{prev_brother_bend, brother_bend};
                return Circuit(prev_line, last_line);
            }
        }
    }
    return Circuit();
}

Circuit CircuitFinder::find_last_circuit_backward(const Bend& last_end_bend)
{
    if (last_end_bend.get_prev_links_qty()==0) {
        return Circuit();
    }
    if (last_end_bend.get_index_in_master_node() == 0) {
        return Circuit();
    }

    //static size_t search_area{100};
    //size_t current_search_deepening{0};
    
    std::map<Node, Bend> last_line_nodes;
    fill_map_of_prev_nodes_and_bends(last_line_nodes, last_end_bend);
    
    
    Circuit last_circuit = find_last_circuit_with_this(last_line_nodes, last_end_bend);
    return last_circuit;
            

    //return std::vector<Circuit>();
}



}
