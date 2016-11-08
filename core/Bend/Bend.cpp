
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

Bend& Bend::operator=(const Bend &other)
{
    if (this != &other) {
        this->data = other.data;
    }
    return *this;
}


bool Bend::operator==(const Bend &other) const
{
    return this->data == other.data;
}




bool Bend::is_this_last_bend_in_chain() const {
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

bool Bend::isEmpty() const
{
    return data == nullptr;
}

Node* Bend::getNode() const
{
    return data->node;
}

std::size_t Bend::getPrevBendsSize() const
{
    return data->prevBend.size();
}
std::size_t Bend::getNextBendsSize() const
{
    return data->nextBend.size();
}

Bend& Bend::getPrevBend(std::size_t index) const
{
    if (index >= data->prevBend.size()) {
        throw std::out_of_range("Bend::getPrevBend gets wrong index of Bend");
    }
    return data->prevBend[index];
}
Bend Bend::getNextBend(std::size_t index) const
{
    if (index >= data->nextBend.size()) {
        throw std::out_of_range("Bend::getNextBend gets wrong index of Bend");
    }
    return data->nextBend[index];
}

const std::vector<Bend>& Bend::get_array_of_prev_bends() const
{
    return data->prevBend;
}
const std::vector<Bend>& Bend::get_array_of_next_bends() const
{
    return data->nextBend;
}



}


