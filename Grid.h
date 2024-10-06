#pragma once
#include <fstream>
#include <iostream>
#include <vector>


class Grid {
public:
    const int BOARD_WIDTH = 80;
    const int BOARD_HEIGHT = 25;
    std::vector<std::vector<char>> grid;

    Grid(): grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}
};
