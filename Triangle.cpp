#include "Figure.h"
#include <memory>

void Triangle::draw(std::shared_ptr<Grid>& grid, const char& symbol) {
   if (height <= 0) return;

   for (int i = 0; i < height; ++i) {
      int leftMost = x - i;
      int rightMost = x + i;
      int posY = y + i;

      if (posY < grid->BOARD_HEIGHT) {
         if (leftMost >= 0 && leftMost < grid -> BOARD_WIDTH) {
            grid->grid[posY][leftMost] = symbol;
         }
         if (rightMost >= 0 && rightMost < grid -> BOARD_WIDTH && leftMost != rightMost) {
            grid->grid[posY][rightMost] = symbol;
         }
      }
   }

   for (int i = 0; i < 2 * height - 1; ++i) {
      int baseX = x - height + 1 + i;
      int baseY = y + height - 1;
      if (baseX >= 0 && baseX < grid->BOARD_WIDTH && baseY < grid->BOARD_HEIGHT) {
         grid->grid[baseY][baseX] = symbol;
      }

   }
}

std::string Triangle::getInfo(int& id) {
   return std::to_string(id) + " square " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(height);
}

bool Triangle::isSameFigure(std::shared_ptr<Figure> &other) {
   Triangle* ptr = dynamic_cast<Triangle*>(other.get());
   if (ptr != nullptr) {
      return x == ptr->x && y == ptr->y && height == ptr->height;
   }
   return false;
}

