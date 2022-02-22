#include "pch.h"

uint32_t IPv4toUINT32(std::string);
std::string UINT32toIPv4(uint32_t);

bool isValidIPv4(std::string);

template <typename T>
void printIPv4Range(T first, T second, std::ostream *output_stream)
{
    std::pair<T,T> p = std::minmax(first, second);
    for (T entry = p.first; entry <= p.second; entry++)
    {
        *output_stream << UINT32toIPv4(entry) << std::endl;
    }
}