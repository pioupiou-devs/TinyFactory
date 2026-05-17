#pragma once

#include <vector>
#include <iostream>

class GridSystem
{
public:
    GridSystem();

    void initialize();
    void render();
    void setCell(int x, int y, char value);
    void tick();
    void tickMiner(size_t x, size_t y);
    void tickConveyor(size_t x, size_t y);

private:
    static constexpr int SIZE = 10;
    static constexpr char EMPTY_CELL = '.';
    static constexpr char MINER_CELL = 'M';
    static constexpr char CONVEYOR_CELL = '>';

    std::vector<std::vector<char>> grid;
    std::vector<std::vector<int>> ore;
    std::vector<std::vector<int>> items;
    std::vector<std::vector<int>> nextItems;

    char& getLeftType(size_t x, size_t y);
};