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
    items = std::vector<std::vector<int>>(
        SIZE,
        std::vector<int>(SIZE, 0));
    nextItems = std::vector<std::vector<int>>(
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
            if (line[y] == CONVEYOR_CELL)
                std::cout << '(' << items[x][y] << ')';
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

    if (value != MINER_CELL && value != CONVEYOR_CELL)
    {
        std::cerr << "Invalid value\n";
        return;
    }

    grid[x][y] = value;
}

void GridSystem::tick()
{
    // reset buffer
    nextItems = items;

    // 1. miners produce
    for (size_t x = 0; x < grid.size(); x++)
    {
        for (size_t y = 0; y < grid[x].size(); y++)
        {
            if (grid[x][y] == MINER_CELL)
                tickMiner(x, y);
        }
    }

    // 2. conveyors move
    for (size_t x = 0; x < grid.size(); x++)
    {
        for (size_t y = 0; y < grid[x].size(); y++)
        {
            if (grid[x][y] == CONVEYOR_CELL)
                tickConveyor(x, y);
        }
    }

    // 3. commit
    items = nextItems;
}

void GridSystem::tickMiner(size_t x, size_t y)
{
    ore[x][y]++;
}

void GridSystem::tickConveyor(size_t x, size_t y)
{
    // pull from LEFT
    if (y <= 0)
        return;

    switch (getLeftType(x, y))
    {
    case MINER_CELL:
        // if there's ores in the linked miner
        if (ore[x][y - 1] > 0)
        {
            ore[x][y - 1]--;
            nextItems[x][y] += 1;
            return;
        }
        break;
    case CONVEYOR_CELL:
        // if there's ores in the linked conveyor
        if (items[x][y - 1] > 0)
        {
            nextItems[x][y] += 1;
            return;
        }
        break;

    default:
        break;
    }
}

char &GridSystem::getLeftType(size_t x, size_t y)
{
    return grid[x][y - 1];
}
