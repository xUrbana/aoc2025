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
    for (const auto &range : std::views::split(line, ','))
    {
        auto split_range = range | std::views::split('-');
        std::vector<std::string> parts = std::ranges::to<std::vector<std::string>>(split_range);
        co_yield std::make_pair(
            std::stoull(parts[0]),
            std::stoull(parts[1])
        );
    }
}

uint64_t range_invalid_id_sum(uint64_t start, uint64_t end, const auto &id_checker)
{
    uint64_t invalid_id_sum = 0;
    for (auto s = start; s <= end; s++)
    {
        if (id_checker(s))
        {
            invalid_id_sum += s;
        }
    }
    return invalid_id_sum;
}

void solve(auto &id_checker)
{
    uint64_t invalid_id_sum = 0;
    for (const auto &[start, end] : read_ranges("input.txt"))
    {
        invalid_id_sum += range_invalid_id_sum(start, end, id_checker);
    }
    std::println("{}", invalid_id_sum);
}

void test(range_type r, uint64_t expected_sum, auto &id_checker)
{
    auto &[start, end] = r;
    assert(range_invalid_id_sum(start, end, id_checker) == expected_sum);
}

auto make_tester(const auto &func)
{
    return [&](range_type r, uint64_t sum) { test(r, sum, func); };
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

    void solve()
    {
        ::solve(is_invalid_id);
    }

    void test()
    {
        auto _test = make_tester(is_invalid_id);
        _test({11, 22}, 33);
    }
}

namespace p2
{
    bool is_invalid_id(uint64_t n)
    {
        std::string s = std::to_string(n);
        std::string_view sv = std::string_view(s);

        // id invalid if is made of some sequence of digits repeated at last twice
        // check each substring s[:n+1], check each subslice pass
        for (size_t i = 0; i < s.size() / 2; i++)
        {
            auto ss = sv.substr(0, i+1);

            // 111 means we need to loop twice so (s.size() - len(ss)) / len(ss) = (3 - 1) / 1 = 2;
            // 12121212 is (8 - 2) / 2 = 3
            bool check_next_ss = false;
            for (size_t j = i+1; j < sv.size(); j += ss.size())
            {
                auto next_ss = sv.substr(j, ss.size());

                // next_ss is next substring after the initial ss, if it does not match we can quit early
                if (ss != next_ss)
                {
                    check_next_ss = true;
                    break;
                }
            }

            if (!check_next_ss)
            {
                // we matched through the entire string
                return true;
            }
        }

        return false;
    }

    void solve()
    {
        ::solve(is_invalid_id);
    }

    void test()
    {
        auto _test = make_tester(is_invalid_id);
        _test({11, 22}, 33);
        _test({95, 115}, 210);
        _test({1188511880, 1188511890}, 1188511885);
        _test({1698522, 1698528}, 0);
    }
}

int main()
{
    p1::test();
    p1::solve();
    p2::test();
    p2::solve();
}