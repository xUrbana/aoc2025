#pragma once
#include <generator>
#include <vector>
namespace utils
{
    std::generator<std::string> read_lines(const std::string &file);
    std::vector<std::string> read_grid(const std::string &file);
}