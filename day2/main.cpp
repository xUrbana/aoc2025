#include "../utils.hpp"
#include <ranges>
#include <cstdint>
#include <string>
#include <print>
#include <ranges>
#include <vector>
#include <cassert>

using range_type = std::pair<uint64_t, uint64_t>;

std::generator<range_type> read_ranges(const std::string &file)
{
    const auto line = *utils::read_lines("input.txt").begin();
    auto split_comma = line | std::views::split(',');
    for (const auto &range : split_comma)
    {
        auto split_range = range | std::views::split('-');
        std::vector<std::string> parts = std::ranges::to<std::vector<std::string>>(split_range);
        co_yield std::make_pair(
            std::stoull(parts[0]),
            std::stoull(parts[1])
        );
    }
}


namespace p1
{
    bool is_invalid_id(uint64_t n)
    {
        std::string s = std::to_string(n);

        // if s is odd size it cannot have a number repeated exactly once, therefore it is valid
        if (s.size() % 2 == 1)
            return false;

        // if the first half of the string is equal to the second half, it is invalid
        return s.substr(0, s.size() / 2) == s.substr(s.size() / 2);
    }

    uint64_t range_invalid_id_sum(uint64_t start, uint64_t end)
    {
        uint64_t invalid_id_sum = 0;
        for (auto s = start; s <= end; s++)
        {
            if (is_invalid_id(s))
                invalid_id_sum += s;
        }
        return invalid_id_sum;
    }

    void solve()
    {
        uint64_t invalid_id_sum = 0;
        for (const auto &[start, end] : read_ranges("input.txt"))
        {
           invalid_id_sum += range_invalid_id_sum(start, end);
        }
        std::println("{}", invalid_id_sum);
    }

    void test(range_type r, uint64_t expected_sum)
    {
        auto &[start, end] = r;
        assert(range_invalid_id_sum(start, end) == expected_sum);
    }

    void test()
    {
        test({11, 22}, 33);
    }
}

int main()
{
    p1::test();
    p1::solve();
}