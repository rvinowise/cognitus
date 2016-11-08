#pragma once


#include <vector>
#include <set>
#include <memory>


namespace core {

class Bend;
class Node;


typedef std::size_t Input_iteration;

struct Activation_interval
{
    Input_iteration start;
    Input_iteration end;
};

class Bend_data
{
public:
    Bend_data() {}
    //Bend_data(const Bend_data& other) = default;

    std::vector<Bend> prevBend;
    std::vector<Bend> nextBend;
    Node* node;
    Activation_interval interval;

private:
    std::set<Bend> firedBend;
};

class Bend
{
public:
    Bend();
    Bend(Node& masterNode);
    Bend(const Bend& other);
    ~Bend();
    Bend& operator=(const Bend& other);
    bool operator==(const Bend& other) const;

    bool is_this_last_bend_in_chain() const;
    void connect_to(Bend& toBend);
    bool isEmpty() const;
    Node* getNode() const;

    std::size_t getPrevBendsSize() const;
    std::size_t getNextBendsSize() const;
    Bend &getPrevBend(std::size_t index) const;
    Bend getNextBend(std::size_t index) const;

    const std::vector<Bend>& get_array_of_prev_bends() const;
    const std::vector<Bend>& get_array_of_next_bends() const;

private:
    Bend_data* data;

#ifdef debug_mode
    std::size_t indexInput;
#endif
};


}
