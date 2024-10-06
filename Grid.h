#pragma once
#include <fstream>
#include <iostream>
#include <vector>


struct Cell {
    char symbol = ' ';
    int id;
};

class Grid {
public:
    const int BOARD_WIDTH = 80;
    const int BOARD_HEIGHT = 25;
    std::vector<std::vector<Cell>> grid;

    Grid() : grid(BOARD_HEIGHT, std::vector<Cell>(BOARD_WIDTH)) {}
};
