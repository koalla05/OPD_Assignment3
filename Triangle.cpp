#include "Figure.h"
#include <memory>

void Triangle::frame_draw(std::shared_ptr<Grid>& grid, char symbol) {
   if (symbol == '*') symbol = color[0];
   if (height <= 0) return;

   for (int i = 0; i < height; ++i) {
      int leftMost = x - i;
      int rightMost = x + i;
      int posY = y + i;

      if (posY < grid->BOARD_HEIGHT) {
         if (leftMost >= 0 && leftMost < grid -> BOARD_WIDTH) {
            if (symbol == ' ') {
               grid->grid[posY][leftMost].id = 0;
            }
            grid->grid[posY][leftMost].symbol = symbol;
            grid->grid[posY][leftMost].id = id;
         }
         if (rightMost >= 0 && rightMost < grid -> BOARD_WIDTH && leftMost != rightMost) {
            if (symbol == ' ') {
               grid->grid[posY][rightMost].id = 0;
            }
            grid->grid[posY][rightMost].symbol = symbol;
            grid->grid[posY][rightMost].id = id;
         }
      }
   }

   for (int i = 0; i < 2 * height - 1; ++i) {
      int baseX = x - height + 1 + i;
      int baseY = y + height - 1;
      if (baseX >= 0 && baseX < grid->BOARD_WIDTH && baseY < grid->BOARD_HEIGHT) {
         if (symbol == ' ') {
            grid->grid[baseY][baseX].id = 0;
         }
         grid->grid[baseY][baseX].symbol = symbol;
         grid->grid[baseY][baseX].id = id;
      }

   }
}

void Triangle::fill_draw(std::shared_ptr<Grid> &grid, char symbol) {
   if (symbol == '*') symbol = color[0];
   if (height <= 0) return;

   for (int i = 0; i < height; ++i) {
      int leftMost = x - i;
      int rightMost = x + i;
      int posY = y + i;

      if (posY < grid->BOARD_HEIGHT) {
         for (int posX = leftMost; posX <= rightMost; ++posX) {
            if (posX >= 0 && posX < grid->BOARD_WIDTH) {
               if (symbol == ' ') {
                  grid->grid[posY][posX].id = 0;
               }
               grid->grid[posY][posX].symbol = symbol;
               grid->grid[posY][posX].id = id;
            }
         }
      }
   }
}


std::string Triangle::getInfo() {
   return std::to_string(id) + " square " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(height);
}

bool Triangle::isSameFigure(std::shared_ptr<Figure> &other) {
   Triangle* ptr = dynamic_cast<Triangle*>(other.get());
   if (ptr != nullptr) {
      return x == ptr->x && y == ptr->y && height == ptr->height;
   }
   return false;
}

