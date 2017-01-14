#include "CircuitFinder.h"

namespace core {

CircuitFinder::CircuitFinder()
{

}

std::vector<Circuit> CircuitFinder::find_circuits_backward(const Bend& initialBend)
{
    if (initialBend.get_prev_links_qty()==0) {
        return std::vector<Circuit>();
    }

    //for (Bend prevBend = initialBend.getPrevBend()


    //return std::vector<Circuit>();
}



}
