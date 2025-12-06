#include "../utils.hpp"
#include <vector>
#include <cassert>
#include <array>
#include <print>

class Grid
{
    using GridType = std::vector<std::string>;
    using GridIndex = std::pair<size_t, size_t>;
    using Direction = std::pair<int8_t, int8_t>;
    static constexpr Direction N  = std::make_pair(1, 0);
    static constexpr Direction E  = std::make_pair(0, 1);
    static constexpr Direction S  = std::make_pair(-1, 0);
    static constexpr Direction W  = std::make_pair(0, -1);
    static constexpr Direction NE = std::make_pair(1, 1);
    static constexpr Direction SE = std::make_pair(-1, 1);
    static constexpr Direction SW = std::make_pair(-1, -1);
    static constexpr Direction NW = std::make_pair(1, -1);
    static constexpr std::array<Direction, 8> Directions = {
    N, E, S, W, NE, SE, SW, NW
    };
    static constexpr char TOILET_PAPER = '@';
public:
    Grid(GridType &&grid) : grid_(std::move(grid))
    {

    }

    size_t count_accessible_rolls(bool recurse = false)
    {
        std::vector<GridIndex> removed;
        size_t accessible_rolls = 0;

        for (size_t row = 0; row < grid_.size(); row++)
        {
            for (size_t col = 0; col < grid_[row].size(); col++)
            {
                // If its not toilet paper, no reason to check
                if (grid_[row][col] != '@') continue;

                size_t roll_count = 0;
                for (const auto &d : Directions)
                {
                    const auto [new_row, new_col] = index_at_dir(d, row, col);
                    if (is_toilet_paper(new_row, new_col))
                        roll_count++;
                }

                if (roll_count < 4)
                {
                    accessible_rolls++;
                    if (recurse)
                        removed.push_back(std::make_pair(row, col));
                }
            }
        }

        if (recurse && !removed.empty())
        {
            for (const auto &[row, col] : removed)
            {
                grid_[row][col] = '.';
            }
            accessible_rolls += count_accessible_rolls(true);
        }

        return accessible_rolls;
    }

private:

    GridIndex index_at_dir(const Direction &d, size_t row, size_t col)
    {
        auto [row_offset, col_offset] = d;
        return std::make_pair(row + row_offset, col + col_offset);
    }

    bool is_toilet_paper(size_t row, size_t col) const
    {
        if ((row >= 0 && row < grid_.size()) &&
            (col >= 0 && col < grid_[row].size()))
        {
            return grid_[row][col] == TOILET_PAPER;
        }

        return false;
    }

    GridType grid_;
};

namespace p1
{
    void solve()
    {
        auto grid = Grid(utils::read_grid("input.txt"));
        std::println("{}", grid.count_accessible_rolls());
    }

    void test()
    {
        auto grid = Grid(utils::read_grid("test_input.txt"));
        assert(grid.count_accessible_rolls() == 13);
    }
}

namespace p2
{
    void solve()
    {
        auto grid = Grid(utils::read_grid("input.txt"));
        std::println("{}", grid.count_accessible_rolls(true));
    }
    void test()
    {
        auto grid = Grid(utils::read_grid("test_input.txt"));
        auto rolls = grid.count_accessible_rolls(true);
        std::println("{}", rolls);
        assert(rolls == 43);
    }
}

int main()
{
    p1::test();
    p1::solve();
    p2::test();
    p2::solve();
}