#include <iostream>
#include "GridSystem.h"

int main()
{
    GridSystem g;

    while (true)
    {
        std::cout << "----------------------\n\n";
        g.render();
        std::cout << "----------------------\n";

        std::string command;
        int x, y;

        std::cin >> command >> x >> y;

        if (command == "place")
            g.setCell(x, y, 'M');
        else
            std::cerr << "Invalid command\n";
    }
}