#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <exception>

#include <interface/common/coordinates_type.h>



template<typename Cont1, typename Cont2/*, typename T*/>
//using T = typename Cont1::value_type;
std::vector<typename Cont1::value_type>
get_items_of_difference(Cont1& cont1, Cont2& cont2)
{
    std::vector<typename Cont1::value_type> result;
    for (const typename Cont1::value_type t1: cont1)
    if (
        std::find(cont2.begin(), cont2.end(), t1)
        ==
        cont2.end()
    ) {
        result.push_back(t1);
    }
    return result;
}


template<typename Cont,
         typename Unit = typename Cont::value_type,
         typename Iterator = typename Cont::iterator>
Unit& get_unit_in_margin(Cont& container)
{
    if (container.empty()) {
        throw("get_unit_in_margin for a container without units" );
    }
    Unit* unit_in_margin = &container.front();
    for (Iterator iterator = ++container.begin();
         iterator != container.end();
         ++iterator) {

        Unit& unit = *iterator;
        if (unit.position.x() > unit_in_margin->position.x()) {
            unit_in_margin = &unit;
        }
    }
    return *unit_in_margin;
}


template <typename Cont,
          typename Item>
bool contains(const Cont& container, const Item& item)
{
    return std::find(container.begin(), container.end(), item) != container.end();
}


using render::Point;
template <typename Cont,
          typename Unit = typename Cont::value_type,
          typename Iterator = typename Cont::iterator>
Point get_center_among_of(const Cont& container)
{
    if (container.size()==0) {
        throw("get_center_among_of for a container without units" );
    }
    Point center{0,0};
    for (const Unit& unit: container) {
        center += unit.position();
    }
    center /= container.size();

    return center;
}
