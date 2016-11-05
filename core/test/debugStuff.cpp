#include "debugStuff.h"

#include <QDebug>
#include <iostream>

namespace test {

Debug_inspector debug;

void Debug_inspector::message(const std::string& _message)
{
    message(ALL, _message.c_str());
}
void Debug_inspector::message(const char* _message)
{
    message(ALL, _message);
}


void Debug_inspector::message(Debug_index this_debug_index, const char* message)
{
#ifdef debug_msg_core

    if (debug_index == NONE) {
        return;
    }

    if (
            (this_debug_index == debug_index) ||
            (this_debug_index == ALL) ||
            (debug_index == ALL)
        )
    {
        //std::cout << message << "\n";
        qDebug(message);
    }
#endif
}


void Debug_inspector::message(const boost::format& _message)
{
    message(_message.str());
}
void Debug_inspector::message(Debug_index this_debug_index, const boost::format& _message)
{
    message(this_debug_index, _message.str().c_str());
}


void Debug_inspector::error(const boost::format& _message)
{
    message(Debug_index::ALL, _message);
}
void Debug_inspector::error(const std::string& _message)
{
    message(Debug_index::ALL, _message.c_str());
}

void Debug_inspector::verify(bool statement, const char *statementStr, const char *description,
        const char *file, unsigned int line)
{
    if (!statement) {
        std::string error = (boost::format("fail: %1% at %2% line %3% \n%4%")
                                          %statementStr %file %line %description).str();
        message(error);
        errors.push_back(error);
    } else {
        uint32_t qtySameStatements = passedStatements.count(statementStr);
        passedStatements.emplace(std::string(statementStr), qtySameStatements+1);
    }

}


void Debug_inspector::writeResume()
{
    message("\nresume");
    if (errors.size() > 0) {
        message(boost::format("%1% errors catched")% errors.size());
        for (auto _message : errors) {
            error(_message);
        }
    } else {
        message(boost::format("%1% verifications are passed") %passedStatements.size());
        for (auto _message: passedStatements) {
            message(_message.first);
        }
    }
}


}
