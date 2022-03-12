#include "pch.h"
#include "ipgen.h"

void parseArguments(std::string, std::ostream *);
void processArguments(std::istream *, std::ostream *);

// Configuration flags
struct
{
    bool sorted = false;
} flags;

int main(int argc, char *argv[])
{
    std::stringstream buffer_stream;
    std::ostream *output_stream = &std::cout;

    // Help
    if (argc != 2)
    {
        *output_stream << "Usage: " << argv[0] << " EXPR[,EXPR...]" << std::endl;
        exit(1);
    }

    // Parse
    parseArguments(argv[1], &buffer_stream);

    // Process
    processArguments(&buffer_stream, output_stream);

    exit(0);
}

void parseArguments(std::string arguments, std::ostream *output_stream)
{
    std::stringstream arguments_stream(arguments);
    std::string token;
    while (std::getline(arguments_stream, token, ','))
    {
        *output_stream << token << std::endl;
    }
};

void processArguments(std::istream *input_stream, std::ostream *output_stream)
{
    std::list<uint32_t> addresses;
    int cidr;
    std::string first, second, argument;
    while (std::getline(*input_stream, argument))
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
                printIPv4Range(IPv4toUINT32(first), IPv4toUINT32(second), output_stream);
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

                    printIPv4Range(u - (u & mask), u | mask, output_stream);
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
                    *output_stream << argument << std::endl;
                }
                else
                {
                    std::cerr << "Invalid input: " << argument << std::endl;
                }
            }
        }
    }
};