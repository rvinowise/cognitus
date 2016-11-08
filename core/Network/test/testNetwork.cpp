#include "core/Network/test/testNetwork.h"
#include "core/Network/Interface/Input/test/testInput.h"
#include "core/Network/Network.h"

#include <boost/format.hpp>
#include "core/test/Debug_inspector.h"

namespace test {


void Network::init_data_for_tests()
{
    unsigned int randomSeed = std::chrono::system_clock::now().time_since_epoch().count();
    std::srand(randomSeed);
    debug.message(boost::format("random seed=%1%")% randomSeed);
}

void Network::work_of_network()
{
    test::Input input;
    input.bring_inputs_to_representation_of_network();

}




}
