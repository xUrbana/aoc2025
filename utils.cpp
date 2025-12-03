#include "utils.hpp"
#include <fstream>

namespace utils
{
    std::generator<std::string> read_lines(const std::string &file)
    {
        std::ifstream input(file);
        if (!input.is_open())
        {
            throw std::invalid_argument("Failed to open input file.");
        }

        std::string line;
        while (std::getline(input, line))
            co_yield line;
    }
}