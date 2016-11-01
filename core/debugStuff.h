#pragma once


#include <boost/format.hpp>
//#define debug public

enum Debug_index {NONE, ALL, BAD_WAIT};
constexpr Debug_index global_debug_index = NONE;


void debug_msg(Debug_index this_debug_index, const std::string& message);

void debug_msg(Debug_index this_debug_index, const boost::format& message);
void debug_msg(const boost::format& message);

void error_msg(const boost::format &message);
