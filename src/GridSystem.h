#pragma once

#include <vector>
#include <iostream>
#include "Cell.h"

class GridSystem
{
public:
    GridSystem();

    void render();
    void setCell(size_t x, size_t y, char value);
    const Cell& getCell(size_t x, size_t y);
    void tick();
    void tickMiner(size_t x, size_t y);
    void tickConveyor(size_t x, size_t y);
    void moveOreFromDirection(size_t x, size_t y);

private:
    static constexpr int SIZE = 10;

    std::vector<std::vector<Cell>> grid;
    std::vector<std::vector<Cell>> nextGrid;

    std::pair<int, int> getLinkedNeighborPosition(size_t x, size_t y, Direction dir);
};