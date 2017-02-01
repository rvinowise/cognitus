#include "core/Network/test/testNetwork.h"
#include "core/Network/Interface/Input/test/testInput.h"
#include "core/Network/Network.h"

#include <boost/format.hpp>
#include "core/test/Debug_inspector.h"
#include "core/test/randomFunc.h"
#include "core/Bend/Figure_bend/Figure_bend.h"
#include "core/Bend/Figure_bend/Iterator/Iterator_BFS.h"

namespace test {

using std::size_t;
using std::vector;

void Network::init_common_data_for_all_tests()
{
    unsigned int randomSeed = std::chrono::system_clock::now().time_since_epoch().count();
    std::srand(randomSeed);
    debug.message(boost::format("random seed=%1%")% randomSeed);
}

void Network::work_of_network()
{
    //test::Input input(network);
    //input.bring_inputs_to_representation_of_network();

    deallocation_of_all_entities();
}

void Network::construct_network_ignoring_interface()
{
    network.input.initNodes(2+random(10));
    network.output.initNodes(2+random(10));

    vector<Node> nodes(random(100));

    for (Node node: nodes) {
        size_t figure_size = random(100);
        node.generate_random_empty_figure(figure_size);
        for (Figure_bend figure: node) {

        }
    }

    Node node = network.input.getNode(0);
    Bend bend = node.add_bend();


    /*Node node1_lvl2();
    Figure_bend figure1_node1_lvl2 = node1_lvl2.get_lower_chain_bend();
    figure1_node1_lvl2.


    Node node_2_lvl_2();*/

}

void Network::deallocation_of_all_entities()
{
    construct_network_ignoring_interface();
}




}
