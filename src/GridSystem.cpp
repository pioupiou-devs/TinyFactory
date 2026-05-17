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
    inventory = std::vector<std::vector<int>>(
        SIZE,
        std::vector<int>(SIZE, 0));
    nextInventory = std::vector<std::vector<int>>(
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
            if (line[y] == CONVEYOR_CELL || line[y] == MINER_CELL)
                std::cout << '(' << inventory[x][y] << ')';
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
    nextInventory = inventory;

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
    inventory = nextInventory;
}

void GridSystem::tickMiner(size_t x, size_t y)
{
    nextInventory[x][y]++;
}

void GridSystem::tickConveyor(size_t x, size_t y)
{
    switch (getLeftType(x, y))
    {
    case MINER_CELL:
        moveOreFromLeft(x, y);
        break;
    case CONVEYOR_CELL:
        moveOreFromLeft(x, y);
        break;

    default:
        break;
    }
}

void GridSystem::moveOreFromLeft(size_t x, size_t y)
{
    if (inventory[x][y - 1] <= 0)
        return;

    nextInventory[x][y - 1]--;
    nextInventory[x][y] += 1;
}

char GridSystem::getLeftType(size_t x, size_t y)
{
    if (y == 0)
        return EMPTY_CELL;

    return grid[x][y - 1];
}
