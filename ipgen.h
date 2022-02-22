#include "pch.h"

uint32_t IPv4toUINT32(std::string);
std::string UINT32toIPv4(uint32_t);

bool isValidIPv4(std::string);

template <typename T>
std::list<T> expandRange(T first, T second)
{
    std::pair<T,T> p = std::minmax(first, second);
    std::list<T> list;
    for (T entry = p.first; entry <= p.second; entry++)
    {
        list.push_back(entry);
    }
    return list;
}