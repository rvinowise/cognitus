#include "CircuitFinder.h"

namespace core {

CircuitFinder::CircuitFinder()
{

}

std::vector<Circuit> CircuitFinder::find_circuits_backward(const Bend& initialBend)
{
    if (initialBend.getPrevBendsSize()==0) {
        return std::vector<Circuit>();
    }

    //for (Bend prevBend = initialBend.getPrevBend()


    //return std::vector<Circuit>();
}



}
