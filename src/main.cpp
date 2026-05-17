#include <iostream>
#include "GridSystem.h"
#include "main.h"

int main()
{
    bool running = true;
    GridSystem g;

    while (running)
    {
        // Take user input
        ProcessInput(g, running);

        // Tick
        g.tick();

        // Render
        Render(g);
    }
}

void Render(GridSystem &g)
{
    std::cout << "----------------------\n\n";
    g.render();
    std::cout << "----------------------\n";
}

void ProcessInput(GridSystem &g, bool &running)
{
    std::string command;
    int x, y;

    std::cin >> command >> x >> y;

    if (command == "place")
        g.setCell(x, y, 'M');
    else if (command == "exit")
        running = false;
}