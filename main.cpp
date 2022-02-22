#include "pch.h"
#include "ipgen.h"

std::list<std::string> parseArguments(std::string);
std::list<uint32_t> processArguments(std::list<std::string>);

// Configuration flags
struct
{
    bool sorted = false;
} flags;

int main(int argc, char *argv[])
{
    // Help
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " EXPR[,EXPR...]" << std::endl;
        exit(1);
    }

    // Parse
    std::list<std::string> arguments = parseArguments(argv[1]);

    // Process
    std::list<uint32_t> addresses = processArguments(arguments);

    // Print
    for (uint32_t &address : addresses)
    {
        std::cout << UINT32toIPv4(address) << std::endl;
    }

    exit(0);
}

std::list<std::string> parseArguments(std::string arguments)
{
    std::list<std::string> list;
    std::stringstream stream(arguments);
    std::string token;
    while (std::getline(stream, token, ','))
    {
        list.push_back(token);
    }
    return list;
};

std::list<uint32_t> processArguments(std::list<std::string> arguments)
{
    std::list<uint32_t> addresses;
    int cidr;
    std::string first, second;
    for (std::string &argument : arguments)
    {
        std::size_t pos;
        // is a IP range
        pos = argument.find('-');
        if (pos != std::string::npos)
        {
            first = argument.substr(0, pos);
            second = argument.substr(pos + 1);

            if (isValidIPv4(first) && isValidIPv4(second))
            {
                std::list<uint32_t> list = expandRange<uint32_t>(IPv4toUINT32(first), IPv4toUINT32(second));
                addresses.splice(addresses.end(), list);
            }
            else
            {
                std::cerr << "Invalid input: " << argument << std::endl;
            }
        }
        else
        {
            // is a CIDR
            pos = argument.find('/');
            if (pos != std::string::npos)
            {
                first = argument.substr(0, pos);
                cidr = atoi(argument.substr(pos + 1).c_str());

                if (isValidIPv4(first) && (cidr >= 0 && cidr <= 32))
                {
                    // PLACEHOLDER
                    uint32_t u = IPv4toUINT32(first);
                    uint32_t mask = UINT32_MAX >> cidr;

                    std::list<uint32_t> list = expandRange<uint32_t>(u - (u & mask),u | mask);
                    addresses.splice(addresses.end(), list);
                }
                else
                {
                    std::cerr << "Invalid input: " << argument << std::endl;
                }
            }
            else
            {
                // is IPv4 address
                if (isValidIPv4(argument))
                {
                    addresses.push_back(IPv4toUINT32(argument));
                }
                else
                {
                    std::cerr << "Invalid input: " << argument << std::endl;
                }
            }
        }
    }
    return addresses;
};