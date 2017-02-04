#include "Acquiring_handles.h"

Acquiring_handles::Acquiring_handles():
    handles_qty{1}
{
}

void Acquiring_handles::connect_a_handle()
{
    handles_qty++;
}

void Acquiring_handles::disconnect_a_handle()
{
    handles_qty--;
    /*if (handles_qty == 0) {
        delete this;
    }*/
}
