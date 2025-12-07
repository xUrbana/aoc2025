#include "../utils.hpp"
#include <algorithm>
#include <limits>
#include <vector>
#include <print>
#include <cassert>
#include <ranges>

struct Inventory
{
    using IdType = uint64_t;
    using Ranges = std::vector<utils::Range<IdType>>;
    Ranges fresh_ids;
    std::vector<IdType> ids_to_check;

    Inventory() = default;
    Inventory(const std::string &file)
    {
        bool reading_ranges = true;

        for (const auto &line : utils::read_lines(file))
        {
            if (line.empty())
            {
                reading_ranges = false;
                continue;
            }

            if (reading_ranges)
            {
                fresh_ids.push_back(utils::parse_range<IdType>(line));
            }
            else
            {
                ids_to_check.push_back(utils::parse_num<IdType>(line));
            }
        }
    }
};

namespace p1
{
    size_t check_fresh_ids(const Inventory &inventory)
    {
        size_t total_fresh_ids = 0;
        for (const auto &id : inventory.ids_to_check)
        {
            for (const auto &[start, end] : inventory.fresh_ids)
            {
                if (id >= start && id <= end)
                {
                    total_fresh_ids++;
                    break;
                }
            }
        }
        return total_fresh_ids;
    }

    void solve()
    {
        Inventory inventory("input.txt");
        auto fresh_ids = check_fresh_ids(inventory);
        std::println("{}", fresh_ids);
    }

    void test()
    {
        Inventory inventory("test_input.txt");
        auto fresh_ids = check_fresh_ids(inventory);
        assert(fresh_ids == 3);
    }
}

namespace p2
{
    void test(Inventory::Ranges ranges, uint64_t expected_value)
    {
        /*
        Inventory inventory;
        inventory.fresh_ids = std::move(ranges);
        size_t fresh_id_count = find_fresh_ids_v2(inventory);
        std::println("{} = {} (expected {})", inventory.fresh_ids, fresh_id_count, expected_value);
        assert(fresh_id_count == expected_value);
        */
    }

    void test()
    {
        test({{3,5}, {10,14}, {16,20}, {12,18}}, 14);
        test({{0, 100}, {1, 100}}, 101);
        test({{1,2},{1,3},{1,4}}, 4);
        test({{1, 10}, {3, 5}}, 10);
        test({{1, 10}, {3, 5}, {3, 5}, {6, 7}}, 10);
    }
}

int main()
{
    p1::test();
    p1::solve();
    p2::test();
    //p2::solve();
}

// 343099782171608
// 335107036446171