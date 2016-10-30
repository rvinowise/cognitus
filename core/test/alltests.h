#pragma once
#include <QtTest/QtTest>
#include "core/Network/Network.h"
#include <atomic>

namespace test {

using namespace core;

class Network: public QObject
{
    Q_OBJECT
private slots:
    void init_data_for_tests();
    void work_of_network();

};

extern std::atomic_size_t i_iteration;

class Input: public QObject
{
    Q_OBJECT
public:


public slots:
    void bring_inputs_to_representation_of_network();

private:
    void init_input_characteristics();
    void concoct_input_history();
    void input_history_in_cycle();
    void check_network_validity();
    void check_if_all_bends_of_input_iteration_have_the_same_previous_bends(std::vector<Bend*>* bendsOfIteration);
    void compare_inputted_array_with_nodes_in_network(QBitArray inputIteration, const std::vector<Bend*>* bendsOfIteration);
    std::vector<Bend*>* get_bends_of_previous_input_iteration(const std::vector<Bend*>* bendsOfIteration);

    size_t qtyInputs;
    size_t qtyIterations;

    QVector<QBitArray> inputHistory;
};


uint random(uint max);



}
