#include "GridSystem.h"

GridSystem::GridSystem()
{
    initialize();
}

void GridSystem::initialize()
{
    grid = std::vector<std::vector<char>>(
        SIZE,
        std::vector<char>(SIZE, EMPTY_CELL));
    ore = std::vector<std::vector<int>>(
        SIZE,
        std::vector<int>(SIZE, 0));
}

void GridSystem::render()
{
    for (size_t x = 0; x < grid.size(); x++)
    {
        const auto &line = grid[x];
        for (size_t y = 0; y < line.size(); y++)
        {
            std::cout << line[y];
            if (line[y] == MINER_CELL)
                std::cout << '(' << ore[x][y] << ')';
            std::cout << '\t';
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

void GridSystem::tick()
{
    for (size_t x = 0; x < grid.size(); x++)
    {
        const auto &line = grid[x];
        for (size_t y = 0; y < line.size(); y++)
        {
            if (line[y] == MINER_CELL)
                ore[x][y]++;
        }
    }
}
