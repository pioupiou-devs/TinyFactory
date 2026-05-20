#include "GridSystem.h"

GridSystem::GridSystem()
{
    initialize();
}

void GridSystem::initialize()
{
    grid = std::vector<std::vector<Cell>>(
        SIZE,
        std::vector<Cell>(SIZE, Cell()));
}

void GridSystem::render()
{
    for (size_t x = 0; x < grid.size(); x++)
    {
        const auto &line = grid[x];
        for (size_t y = 0; y < line.size(); y++)
        {
            std::cout << ((Cell)line[y]).toString();
            std::cout << '\t';
        }
        std::cout << '\n';
    }
}

void GridSystem::setCell(size_t x, size_t y, char type)
{
    if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
    {
        std::cerr << "Out of bounds\n";
        return;
    }
    CellType cType = Cell::getTypeFromChar(type);
    if (cType != CellType::MINER && cType != CellType::CONVEYOR)
    {
        std::cerr << "Invalid type\n";
        return;
    }

    grid[x][y] = Cell(type);
}

Cell GridSystem::getCell(size_t x, size_t y)
{
    return grid[x][y];
}

void GridSystem::tick()
{
    // reset buffer
    nextGrid = grid;

    // 1. miners produce
    for (size_t x = 0; x < grid.size(); x++)
    {
        for (size_t y = 0; y < grid[x].size(); y++)
        {
            if (grid[x][y].getType() == CellType::MINER)
                tickMiner(x, y);
        }
    }

    // 2. conveyors move
    for (size_t x = 0; x < grid.size(); x++)
    {
        for (size_t y = 0; y < grid[x].size(); y++)
        {
            if (grid[x][y].getType() == CellType::CONVEYOR)
                tickConveyor(x, y);
        }
    }

    // 3. commit
    grid = nextGrid;
}

void GridSystem::tickMiner(size_t x, size_t y)
{
    int val = grid[x][y].getValue();
    nextGrid[x][y].setValue(++val);
}

void GridSystem::tickConveyor(size_t x, size_t y)
{
    Cell cell = grid[x][y];
    moveOreFromDirection(x, y);
}

void GridSystem::moveOreFromDirection(size_t x, size_t y)
{
    Cell cell = getCell(x, y);

    std::pair neighborPos = getLinkedNeighborPosition(x, y, cell.getDirection());

    Cell neighbor = getCell(neighborPos.first, neighborPos.second);
    if (neighbor.getValue() <= 0)
        return;

    int v1 = neighbor.getValue();
    neighbor.setValue(v1 - 1);
    nextGrid[neighborPos.first][neighborPos.second] = neighbor;

    int v2 = cell.getValue();
    cell.setValue(v2 + 1);
    nextGrid[x][y] = cell;
}

std::pair<int, int> GridSystem::getLinkedNeighborPosition(size_t x, size_t y, Direction dir)
{
    switch (dir)
    {
    default:
    case Direction::RIGHT:
        if (y > 0)
            return std::pair(x, y - 1);
        break;
    case Direction::DOWN:
        if (x <= SIZE)
            return std::pair(x + 1, y);
        break;
    case Direction::LEFT:
        if (y <= SIZE)
            return std::pair(x, y + 1);
        break;
    case Direction::UP:
        if (x > 0)
            return std::pair(x - 1, y);
        break;
    }

    return std::pair(-1, -1);
}
