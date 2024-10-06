#include "Figure.h"

void Square::draw(std::shared_ptr<Grid> &grid, const char& symbol) {
    for (int i = 0; i < height; ++i) {
        int topY = y;
        int bottomY = y + height - 1;
        int posX = x + i;

        if (posX >= 0 && posX < grid->BOARD_WIDTH && topY >= 0 && topY < grid->BOARD_HEIGHT) {
            grid->grid[topY][posX] = symbol;
        }

        if (posX >= 0 && posX < grid->BOARD_WIDTH && bottomY >= 0 && bottomY < grid->BOARD_HEIGHT) {
            grid->grid[bottomY][posX] = symbol;
        }
    }

    for (int i = 0; i < height; ++i) {
        int leftX = x;
        int rightX = x + height - 1;
        int posY = y + i;

        if (leftX >= 0 && leftX < grid->BOARD_WIDTH && posY >= 0 && posY < grid->BOARD_HEIGHT) {
            grid->grid[posY][leftX] = symbol;
        }

        if (rightX >= 0 && rightX < grid->BOARD_WIDTH && posY >= 0 && posY < grid->BOARD_HEIGHT) {
            grid->grid[posY][rightX] = symbol;
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


