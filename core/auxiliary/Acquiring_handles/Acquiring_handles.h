#pragma once
#include <memory>

class Acquiring_handles
{
public:
    Acquiring_handles();

    void connect_a_handle();
    void disconnect_a_handle();
protected:
    std::size_t handles_qty;
};
