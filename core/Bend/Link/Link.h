#pragma once


class Linked
{
public:
    Linked();

    virtual std::size_t get_prev_links_qty() const;
    virtual std::size_t get_next_links_qty() const;
    virtual Linked get_prev_link(std::size_t index) const;
    virtual Linked get_next_link(std::size_t index) const;
};

