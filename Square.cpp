#include "Figure.h"

void Square::frame_draw(std::shared_ptr<Grid> &grid, char symbol) {
    if (symbol == '*') symbol = color[0];
    for (int i = 0; i < height; ++i) {
        int topY = y;
        int bottomY = y + height - 1;
        int posX = x + i;

        if (posX >= 0 && posX < grid->BOARD_WIDTH && topY >= 0 && topY < grid->BOARD_HEIGHT) {
            grid->grid[bottomY][posX].color = color;
            grid->grid[bottomY][posX].symbol = symbol;
        }

        if (posX >= 0 && posX < grid->BOARD_WIDTH && bottomY >= 0 && bottomY < grid->BOARD_HEIGHT) {
            grid->grid[bottomY][posX].color = color;
            grid->grid[bottomY][posX].symbol = symbol;
        }
    }

    for (int i = 0; i < height; ++i) {
        int leftX = x;
        int rightX = x + height - 1;
        int posY = y + i;

        if (leftX >= 0 && leftX < grid->BOARD_WIDTH && posY >= 0 && posY < grid->BOARD_HEIGHT) {
            grid->grid[posY][leftX].color = color;
            grid->grid[posY][leftX].symbol = symbol;
        }

        if (rightX >= 0 && rightX < grid->BOARD_WIDTH && posY >= 0 && posY < grid->BOARD_HEIGHT) {
            grid->grid[posY][rightX].color = color;
            grid->grid[posY][rightX].symbol = symbol;
        }
    }
}

void Square::fill_draw(std::shared_ptr<Grid> &grid, char symbol) {
    if (symbol == '*') symbol = color[0];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < height; ++j) {
            int gridX = x + j;
            int gridY = y + i;

            if (gridX >= 0 && gridX < grid->BOARD_WIDTH && gridY >= 0 && gridY < grid->BOARD_HEIGHT) {
                grid->grid[gridY][gridX].color = color;
                grid->grid[gridY][gridX].symbol = symbol;
            }
        }
    }
}


std::string Square::getInfo(int &id) {
    return std::to_string(id) + " square " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(height);
}

bool Square::isSameFigure(std::shared_ptr<Figure> &other) {
    Square* ptr = dynamic_cast<Square*>(other.get());
    if (ptr != nullptr) {
        return x == ptr->x && y == ptr->y && height == ptr->height;
    }
    return false;
}


