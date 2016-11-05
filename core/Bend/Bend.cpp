
#include "Bend.h"

#include "core/Node/Node.h"

#ifdef debug_mode
#include "core/Node/InterfaceNode.h"
#include "core/Network/Network.h"
#include "core/test/allTests.h"
#include "core/test/randomFunc.h"
#endif

namespace core {

Bend::Bend()
{

}

Bend::Bend(Node& masterNode)
{
    //data = std::unique_ptr<Bend_data>(new Bend_data);
    //data.get()->node = std::shared_ptr<Node>(&masterNode);
	
    data = new Bend_data();
    data->node = &masterNode;

#ifdef debug_mode
    //indexInput = static_cast<InterfaceNode*>(masterNode)->get_index_in_interface_array();
#endif
}

Bend::Bend(const Bend& other)
{
    this->data = other.data;
}

Bend::~Bend()
{

}


bool Bend::operator==(const Bend &other)
{
    return this->data == other.data;
}




bool Bend::is_this_last_bend_in_chain() {
    return data->nextBend.empty();
}




void Bend::connect_to(Bend& toBend)
{
    //this->data.get()->nextBend.push_back(toBend);
    //toBend.data.get()->prevBend.push_back(*this);
    //if ((int)test::random(10000)>0) {
        this->data->nextBend.push_back(toBend);
        toBend.data->prevBend.push_back(Bend(*this));
    //}
}

bool Bend::isEmpty()
{
    return data == nullptr;
}

Node *Bend::getNode()
{
    return data->node;
}

std::vector<Bend> *Bend::getPrevBends()const
{
    return &data->prevBend;
}

std::vector<Bend> *Bend::getNextBends() const
{
    return &data->nextBend;
}

}


