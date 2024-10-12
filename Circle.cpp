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
                    else grid->grid[gridY][gridX].id = id;
                    grid->grid[gridY][gridX].symbol = symbol;
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
                    else grid->grid[gridY][gridX].id = id;
                    grid->grid[gridY][gridX].symbol = symbol;
                }
            }
        }
    }
}


std::string Circle::getInfo() {
    std::string option;
    if (is_filled == true) option = "fill";
    else option = "frame";
    return std::to_string(id) + ' ' + type + ' ' + option + ' ' + color + ' ' + std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(radius);
}

bool Circle::isSameFigure(std::shared_ptr<Figure> &other) {
    Circle* ptr = dynamic_cast<Circle*>(other.get());
    if (ptr != nullptr) {
        return x == ptr->x && y == ptr->y && radius == ptr->radius;
    }
    return false;
}

void Circle::edit_dimension(int dimension) {
    radius = dimension;
}

void Circle::move(int d1, int d2) {
    x = d1;
    y = d2;
}
