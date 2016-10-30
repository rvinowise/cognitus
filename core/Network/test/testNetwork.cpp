#include "core/test/alltests.h"

namespace test {


void Network::init_data_for_tests()
{
    uint randomSeed = 325025712;
    //uint randomSeed = QDateTime::currentMSecsSinceEpoch();
    qsrand(randomSeed);
    qDebug(QString("random seed=%1").arg(randomSeed).toLocal8Bit());
}

void Network::work_of_network()
{
    test::Input input;
    input.bring_inputs_to_representation_of_network();
}


uint random(uint max)
{
    //return qrand();
    return uint( qrand() / (RAND_MAX+1.0) * (max+1.0) );
}

}
