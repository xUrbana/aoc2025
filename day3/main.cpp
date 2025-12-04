#include "../utils.hpp"
#include <cassert>
#include <print>
#include <string>
#include <sstream>

uint64_t joltage(const std::string &bank, uint8_t num_cells)
{
    std::stringstream ss;
    size_t start_pos = 0;
    
    // in each iteration of the loop find the next digit
    // cannot search for next digit further than bank.size()-i+1
    for (int16_t i = num_cells-1; i >= 0; i--)
    {
        size_t largest_digit_index = start_pos;

        for (size_t j = largest_digit_index + 1; j <= bank.size()-i-1; j++)
        {
            if (bank[j] > bank[largest_digit_index])
                largest_digit_index = j;
        }

        start_pos = largest_digit_index + 1;
        ss << bank[largest_digit_index];
    }

    return std::stoull(ss.str());
}

void solve(uint8_t num_cells)
{
    uint64_t sum_of_joltages = 0;
    for (const auto &bank : utils::read_lines("input.txt"))
    {
        sum_of_joltages += joltage(bank, num_cells);
    }
    std::println("{}", sum_of_joltages);
}

void test(const std::string bank, uint64_t expected_joltage, uint8_t num_cells)
{
    assert(joltage(bank, num_cells) == expected_joltage);
}

namespace p1
{
    static constexpr uint8_t NUM_CELLS = 2;

    void test()
    {
        ::test("987654321111111", 98, NUM_CELLS);
        ::test("811111111111119", 89, NUM_CELLS);
        ::test("234234234234278", 78, NUM_CELLS);
        ::test("818181911112111", 92, NUM_CELLS);
    }

    void solve()
    {
        ::solve(NUM_CELLS);
    }
}

namespace p2
{
    static constexpr uint8_t NUM_CELLS = 12;

    void test()
    {
        ::test("987654321111111", 987654321111, NUM_CELLS);
        ::test("811111111111119", 811111111119, NUM_CELLS);
        ::test("234234234234278", 434234234278, NUM_CELLS);
        ::test("818181911112111", 888911112111, NUM_CELLS);
    }

    void solve()
    {
        ::solve(NUM_CELLS);
    }
}

int main()
{
    p1::test();
    p1::solve();
    p2::test();
    p2::solve();
}