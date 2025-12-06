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

    std::vector<std::string> read_grid(const std::string &file)
    {
        std::vector<std::string> grid;
        for (const auto &line : read_lines(file))
        {
            grid.push_back(line);
        }
        return grid;
    }
}