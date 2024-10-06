#include "Figure.h"

void Line::draw(std::shared_ptr<Grid>& grid, const char& symbol) {
    if ( x0 < x1 && y0 < y1) {
        int dx = x1 - x0;
        int dy = y1 - y0;
        int d = 2 * dy - dx;
        int y = y0;
        for (int i = x0; i < x1; ++i) {
            if (i < grid -> BOARD_WIDTH && y < grid -> BOARD_HEIGHT){
                grid->grid[y][i] = symbol;
                if (d > 0) {
                    y++;
                    d -= 2 * dx;
                }
                d += 2 * dy;
            }
        }
    }
}

std::string Line::getInfo(int& id) {
    return std::to_string(id) + " square " + std::to_string(x0) + " " + std::to_string(y0) + " " + std::to_string(x1) + " " + std::to_string(y1);
}

bool Line::isSameFigure(std::shared_ptr<Figure> &other) {
    Line* ptr = dynamic_cast<Line*>(other.get());
    if (ptr != nullptr) {
        return x0 == ptr->x0 && y0 == ptr->y0 && x1 == ptr->x1 && y1 == ptr->y1;
    }
    return false;
}