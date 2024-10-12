#include "Figure.h"

void Line::frame_draw(std::shared_ptr<Grid>& grid, char symbol) {
    if (symbol == '*') symbol = color[0];
    if ( x0 < x1 && y0 < y1) {
        int dx = x1 - x0;
        int dy = y1 - y0;
        int d = 2 * dy - dx;
        int y = y0;
        for (int i = x0; i < x1; ++i) {
            if (i < grid -> BOARD_WIDTH && y < grid -> BOARD_HEIGHT){
                if (symbol == ' ') {
                    grid->grid[y][i].id = 0;
                }
                else grid->grid[y][i].id = id;
                grid->grid[y][i].symbol = symbol;
                if (d > 0) {
                    y++;
                    d -= 2 * dx;
                }
                d += 2 * dy;
            }
        }
    }
}

void Line::fill_draw(std::shared_ptr<Grid> &grid, char symbol) {
    frame_draw(grid, symbol);
}


std::string Line::getInfo() {
    std::string option;
    if (is_filled == true) option = "fill";
    else option = "frame";
    return std::to_string(id) + ' ' + type + ' ' + option + ' ' +  color + ' ' + std::to_string(x0) + ' ' + std::to_string(y0) + ' ' + std::to_string(x1) + ' ' + std::to_string(y1);
}

bool Line::isSameFigure(std::shared_ptr<Figure> &other) {
    Line* ptr = dynamic_cast<Line*>(other.get());
    if (ptr != nullptr) {
        return x0 == ptr->x0 && y0 == ptr->y0 && x1 == ptr->x1 && y1 == ptr->y1;
    }
    return false;
}

void Line::edit_dimension(int d1, int d2) {
    x1 = d1;
    y1 = d2;
}

void Line::move(int d1, int d2, int d3, int d4) {
    x0 = d1;
    y0 = d2;
    x1 = d3;
    y1 = d4;
}

