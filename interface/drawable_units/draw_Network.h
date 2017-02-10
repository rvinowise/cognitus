#pragma once

#include "core/Network/Network.h"\

namespace core {
    class Network;
    class Node;
    class Bend;
    class Hub;
}


namespace render {

class Node;
class Bend;
class Hub;

class Network: public core::Network
{
public:
    Network();

    void draw();

private:
};

}
