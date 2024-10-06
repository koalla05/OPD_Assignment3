#include <cmath>
#include "Figure.h"

void Circle::frame_draw(std::shared_ptr<Grid> &grid, char symbol) {
    if (symbol == '*') symbol = color[0];
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {

            if (std::abs(sqrt(pow(j, 2) + pow(i, 2)) - radius) < 0.3) {

                int gridX = x + j;
                int gridY = y + i;

                if (gridX >= 0 && gridX < grid->BOARD_WIDTH && gridY >= 0 && gridY < grid->BOARD_HEIGHT) {
                    if (symbol == ' ') {
                        grid->grid[gridY][gridX].id = 0;
                    }
                    grid->grid[gridY][gridX].color = color;
                    grid->grid[gridY][gridX].symbol = symbol;
                    grid->grid[gridY][gridX].id = id;

                }
            }
        }
    }
}

void Circle::fill_draw(std::shared_ptr<Grid> &grid, char symbol) {
    if (symbol == '*') symbol = color[0];
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {

            if (sqrt(pow(j, 2) + pow(i, 2)) <= radius) {

                int gridX = x + j;
                int gridY = y + i;

                if (gridX >= 0 && gridX < grid->BOARD_WIDTH && gridY >= 0 && gridY < grid->BOARD_HEIGHT) {
                    if (symbol == ' ') {
                        grid->grid[gridY][gridX].id = 0;
                    }
                    grid->grid[gridY][gridX].color = color;
                    grid->grid[gridY][gridX].symbol = symbol;
                    grid->grid[gridY][gridX].id = id;
                }
            }
        }
    }
}


std::string Circle::getInfo() {
    return std::to_string(id) + " circle " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(radius);
}

bool Circle::isSameFigure(std::shared_ptr<Figure> &other) {
    Circle* ptr = dynamic_cast<Circle*>(other.get());
    if (ptr != nullptr) {
        return x == ptr->x && y == ptr->y && radius == ptr->radius;
    }
    return false;
}