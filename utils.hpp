#pragma once
#include <generator>

namespace utils
{
    std::generator<std::string> read_lines(const std::string &file);
}