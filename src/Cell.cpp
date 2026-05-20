#include "Cell.h"

Cell::Cell()
{
    Cell::type = CellType::EMPTY;
    Cell::direction = Direction::NONE;
    Cell::value = 0;
}

Cell::Cell(char building, int value)
{
    Cell::type = getTypeFromChar(building);
    Cell::direction = getDirectionFromChar(building);
    Cell::value = value;
}

CellType Cell::getType()
{
    return type;
}

char Cell::getTypeAsChar()
{
    switch (type)
    {
    case CellType::CONVEYOR:
        switch (direction)
        {
        default:
        case Direction::RIGHT:
            return CONVEYOR_RIGHT;
        case Direction::UP:
            return CONVEYOR_UP;
        case Direction::DOWN:
            return CONVEYOR_DOWN;
        case Direction::LEFT:
            return CONVEYOR_LEFT;
        }
    case CellType::MINER:
        return MINER;
    default:
        return EMPTY;
    }
}

Direction Cell::getDirection()
{
    return direction;
}

int Cell::getValue()
{
    return value;
}

void Cell::setValue(int val)
{
    value = val;
}

std::string Cell::toString()
{
    std::string res(1, getTypeAsChar());
    if (type == CellType::MINER || type == CellType::CONVEYOR)
        res.append("(").append(std::to_string(value)).append(")");
    return res;
}

/* Static methods */
CellType Cell::getTypeFromChar(char type)
{
    switch (type)
    {
    case CONVEYOR_RIGHT:
    case CONVEYOR_UP:
    case CONVEYOR_DOWN:
    case CONVEYOR_LEFT:
        return CellType::CONVEYOR;
    case MINER:
        return CellType::MINER;
    default:
        return CellType::EMPTY;
    }
}

Direction Cell::getDirectionFromChar(char type)
{
    switch (type)
    {
    case '>':
        return Direction::RIGHT;
    case '^':
        return Direction::UP;
    case 'v':
        return Direction::DOWN;
    case '<':
        return Direction::LEFT;
    case 'M':
    default:
        return Direction::NONE;
    }
}
