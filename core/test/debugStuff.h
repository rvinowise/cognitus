#pragma once


#include <boost/format.hpp>
#include <vector>
#include <string>
#include <map>

namespace test {

enum Debug_index {NONE, ALL, BAD_WAIT};

class Debug_inspector
{
public:

    const Debug_index debug_index = ALL;


    void message(const std::string& message);
    void message(const char* message);

    void message(Debug_index this_debug_index, const char* message);
    void message(Debug_index this_debug_index, const boost::format& message);
    void message(const boost::format& message);
    void error(const boost::format &message);
    void error(const std::string &message);

    void verify(bool statement, const char *statementStr, const char *description,
                const char *file, unsigned int line);

    void writeResume();
private:
    std::vector<std::string> errors;
    std::map<std::string,uint32_t> passedStatements;

};


extern Debug_inspector debug;




#define VERIFY(statement) \
	debug.verify((statement), #statement, "", __FILE__, __LINE__);

#define VERIFY2(statement, description) \
	debug.verify((statement), #statement, description, __FILE__, __LINE__);

}

