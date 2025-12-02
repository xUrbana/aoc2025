#include <cassert>
#include <fstream>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <charconv>
#include <generator>
#include <print>
#include <cstdlib>
#include <vector>

int16_t parse_spin_amount(const std::string &s)
{
    int8_t sign = s[0] == 'L' ? -1 : 1;

    int16_t result;
    std::from_chars(s.data() + 1, s.data() + s.size(), result);

    return result * sign;
}

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

namespace p1
{
    void spin_dial(int16_t &current_position, int16_t spin_amount)
    {
        // spin amount can be > 100 so need to % 100
        current_position = (current_position + spin_amount + 100) % 100;
    }

    void solve()
    {
        int16_t dial = 50;
        uint16_t zero_count = 0;
        for (const auto &line : read_lines("input.txt"))
        {
            spin_dial(dial, parse_spin_amount(line));
            if (dial == 0)
            {
                zero_count++;
            }
        }

        std::println("{}", zero_count);
    }

    int16_t test(int16_t dial, int16_t spin_amount)
    {
        spin_dial(dial, spin_amount);
        return dial;
    }

    void test()
    {
        assert(test(0, -1) == 99);
        assert(test(5, -10) == 95);
        assert(test(50, -68) == 82);
        assert(test(55, -55) == 0);
        assert(test(52, 48) == 0);
        assert(test(95, 5) == 0);
    }

}

namespace p2
{
    uint32_t spin_dial(int16_t &current_position, int16_t spin_amount)
    {
        auto new_position = current_position + spin_amount;
        uint32_t zero_count = 0;

        // crossed 0 boundary
        if (new_position < 0 && current_position != 0)
            zero_count++;

        // add the quotient of this division which is the number of full rotations
        zero_count += std::abs(new_position) / 100;

        // 500 / 100 = 5 but we ended on 0 so count extra time
        if (new_position == 0)
            zero_count++;

        
        // do similar logic as p1 spin_dial
        current_position = ((new_position % 100) + 100) % 100;

        return zero_count;
    }

    void solve()
    {
        int16_t dial = 50;
        uint32_t zero_count = 0;
        for (const auto &line : read_lines("input.txt"))
        {
            auto zero_hits = spin_dial(dial, parse_spin_amount(line));
            zero_count += zero_hits;
        }

        std::println("{}", zero_count);
    }

    void test(std::vector<std::string> v, uint32_t expected_zero_count, int16_t start = 50)
    {
        int16_t dial = start;
        uint32_t zero_count = 0;
        for (const auto &s : v)
        {
            auto spin_amount = parse_spin_amount(s);
            zero_count += spin_dial(dial, spin_amount);
        }

        assert(zero_count == expected_zero_count);
    }

    void test()
    {
        test({"L68","L30","R48","L5","R60","L55","L1","L99","R14","L82"}, 6);
        test({"L150", "L50"}, 2);
        test({"L150", "R50"}, 2);
        test({"R150", "L50"}, 2);
        test({"R150", "R50"}, 2);
        test({"L50"}, 1);
        test({"L651"}, 7);
        test({"R150"}, 2);
        test({"L50", "R100"}, 2);
        test({"L50", "R50"}, 1);
        test({"L50", "L50"}, 1);
        test({"R50", "L50"}, 1);
        test({"R50", "R50"}, 1);
        test({"L500"}, 5, 0);
        test({"L100"}, 1, 0);
    }
}

int main()
{
    p1::test();
    p1::solve();
    p2::test();
    p2::solve();
}