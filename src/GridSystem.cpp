#include "GridSystem.h"

GridSystem::GridSystem()
{
    initialize();
}

void GridSystem::initialize()
{
    grid = std::vector<std::vector<char>>(
        SIZE,
        std::vector<char>(SIZE, EMPTY_CELL)
    );
}

void GridSystem::render()
{
    for (const auto& line : grid)
    {
        for (char val : line)
        {
            std::cout << val << '\t';
        }
        std::cout << '\n';
    }
}

void GridSystem::setCell(int x, int y, char value)
{
    if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
    {
        std::cerr << "Out of bounds\n";
        return;
    }

    if (value != MINER_CELL)
    {
        std::cerr << "Invalid value\n";
        return;
    }

    grid[x][y] = value;
}