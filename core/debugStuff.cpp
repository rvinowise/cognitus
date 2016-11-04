#include "debugStuff.h"

#include <QDebug>

void debug_msg(const std::string& message)
{
    debug_msg(ALL, message);
}


void debug_msg(Debug_index this_debug_index, const std::string& message)
{
#ifdef debug_msg_core

    if (global_debug_index == NONE) {
        return;
    }

    if (
            (this_debug_index == global_debug_index) ||
            (this_debug_index == ALL) ||
            (global_debug_index == ALL)
        )
    {
        qDebug(message.c_str());
    }
#endif
}




void debug_msg(const boost::format& message)
{
    debug_msg(message.str());
}
void debug_msg(Debug_index this_debug_index, const boost::format& message)
{
    debug_msg(this_debug_index, message.str());
}


void error_msg(const boost::format& message)
{
    debug_msg(Debug_index::ALL, message);
}
