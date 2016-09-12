#include "InterfaceNode.h"

#include "core/Network/Network.h"


void InterfaceNode::prepareToFire() {
	isPreparedToFire = true;
}

void InterfaceNode::fire() {
	isPreparedToFire = false;
	Node::fire();
}