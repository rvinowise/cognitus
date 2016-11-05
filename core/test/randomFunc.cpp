#include "randomFunc.h"
#include <random>

namespace test {

unsigned int random(unsigned int max)
{
    return static_cast<unsigned int>( std::rand() / (RAND_MAX+1.0) * (max+1.0) );
}

}
