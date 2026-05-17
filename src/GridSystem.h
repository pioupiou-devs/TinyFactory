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

private:
    static constexpr int SIZE = 10;
    static constexpr char EMPTY_CELL = '.';
    static constexpr char MINER_CELL = 'M';

    std::vector<std::vector<char>> grid;
};