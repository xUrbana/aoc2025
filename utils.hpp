#pragma once
#include <generator>
#include <vector>
#include <charconv>
namespace utils
{
    std::generator<std::string> read_lines(const std::string &file);
    std::vector<std::string> read_grid(const std::string &file);

    template <typename T>
    T parse_num(const std::string_view s)
    {
        T ret{};
        std::from_chars(s.data(), s.data() + s.size(), ret);
        return ret;
    }

    template <typename T>
    using Range = std::pair<T, T>;

    template <typename T>
    Range<T> parse_range(auto &s)
    {
        auto split_range = s | std::views::split('-');
        std::vector<std::string> parts = std::ranges::to<std::vector<std::string>>(split_range);
        return std::make_pair(
            parse_num<T>(parts[0]),
            parse_num<T>(parts[1])
        );
    }

    template <typename T>
    std::generator<Range<T>> read_ranges(const std::string &file)
    {
        const auto line = *utils::read_lines("input.txt").begin();
        for (const auto &range : std::views::split(line, ','))
        {
            co_yield parse_range<T>(range);
        }
    }
}