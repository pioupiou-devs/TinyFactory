#pragma once
#include <string>

enum class CellType
{
    EMPTY,
    MINER,
    CONVEYOR
};
enum class Direction
{
    NONE,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Cell
{
public:
    Cell();
    Cell(char building, int value = 0);

    static CellType getTypeFromChar(char type);
    static Direction getDirectionFromChar(char type);

    CellType getType();
    char getTypeAsChar();
    Direction getDirection();
    int getValue();
    void setValue(int val);
    std::string toString();

private:
    static const char CONVEYOR_RIGHT = '>';
    static const char CONVEYOR_LEFT = '<';
    static const char CONVEYOR_UP = '^';
    static const char CONVEYOR_DOWN = 'v';
    static const char MINER = 'M';
    static const char EMPTY = '.';

    CellType type;
    Direction direction;
    int value = 0;
};