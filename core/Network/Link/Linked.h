#pragma once
#include <memory>

class Linked
{
public:
    Linked();
    ~Linked();

    std::size_t get_prev_links_qty() const;
    std::size_t get_next_links_qty() const;
};

