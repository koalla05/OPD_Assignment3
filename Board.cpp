#include "Board.h"
#include "Figure.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

void Board::print() {
    for (int i = 0; i < grid->BOARD_HEIGHT; ++i) {
        for (int j = 0; j < grid->BOARD_WIDTH; ++j) {
            const Cell& cell = grid->grid[i][j];
            if (cell.id > 0 && figures[cell.id - 1]) {
                std::string color = figures[cell.id - 1] -> color;
                if (color  == "red") {
                    std::cout << "\033[31m" << color[0] << "\033[0m";
                } else if (color == "green") {
                    std::cout << "\033[32m" << color[0] << "\033[0m";
                } else if (color == "blue") {
                    std::cout << "\033[34m" << color[0] << "\033[0m";
                } else if ( color == "yellow") {
                    std::cout << "\033[33m" << color[0] << "\033[0m";
                } else if (color == "magenta") {
                    std::cout << "\033[35m" << color[0] << "\033[0m";
                } else if (color == "cyan") {
                    std::cout << "\033[36m" << color[0] << "\033[0m";
                } else if (color == "white") {
                    std::cout << "\033[37m" << color[0] << "\033[0m";
                } else {
                    std::cout << cell.symbol;
                }
            }
            else {
                std::cout << cell.symbol;
            }
        }
        std::cout << std::endl;
    }
}

void Board::add(std::string& shape, std::string& option, std::string& color, int x, int y, int height) {
    bool isSame = false;
    std::shared_ptr<Figure> figure;
    bool is_filled;
    if (option == "fill") is_filled = true;
    else if (option == "frame") is_filled = false;
    else {
        std::cout << "Something wrong with parameters" << std::endl;
    }

    if (shape == "triangle") {
        figure = std::make_shared<Triangle>(x, y, height, color, is_filled, figures.size() + 1);
    }
    else if (shape == "square") {
        figure = std::make_shared<Square>(x, y, height, color, is_filled, figures.size() + 1);
    }
    else if (shape == "circle") {
        figure = std::make_shared<Circle>(x, y, height, color, is_filled, figures.size() + 1);
    }
    else {
        std::cout << "Something is wrong with parameters" << std::endl;
    }

    for (auto& element: figures) {
        if (element->isSameFigure(figure)) {
            isSame = true;
        }
    }

    if (!isSame) {
        figures.push_back(figure);
        figureOrder.push_back(figure -> id);
        if (figure -> is_filled) figure->fill_draw(grid, color[0]);
        else figure ->frame_draw(grid, color[0]);
    }
    else {
        std::cout << "Such a figure already exists" << std::endl;
    }

}

void Board::add(std::string& shape, std::string& option, std::string& color, int x0, int y0, int x1, int y1) {
    bool isSame = false;
    bool is_filled = false;
    if (option == "fill") is_filled = true;
    else if (option == "frame") is_filled = false;
    else {
        std::cout << "Something wrong with parameters" << std::endl;
        return;
    }

    std::shared_ptr<Figure> figure;
    if (shape == "line") {
        figure = std::make_shared<Line>(x0, y0, x1, y1, color, is_filled, figures.size() + 1);
    }
    else {
        std::cout << "Something is wrong with parameters" << std::endl;
    }

    for (auto& element: figures) {
            if (element->isSameFigure(figure)) {
                isSame = true;
            }
        }
    if (!isSame && figure) {
        figures.push_back(figure);
        figureOrder.push_back(figure -> id);
        if (figure->is_filled) figure->fill_draw(grid, color[0]);
        else figure -> frame_draw(grid, color[0]);
    }
    else {
        std::cout << "Such a figure already exists" << std::endl;
    }

}

void Board::clear() {
    while (!figures.empty()) {
        std::shared_ptr<Figure> removed_figure = figures.back();
        if (removed_figure->is_filled) removed_figure->fill_draw(grid, ' ');
        else removed_figure->frame_draw(grid, ' ');
        figures.pop_back();
    }
}

void Board::list() {
    if (figures.empty()) {
        std::cout << "Sorry, no figures yet" << std::endl;
        return;
    }
    for (const auto& figure: figures) {
        if (figure) {
            std::cout << figure -> getInfo() << std::endl;
        }
    }
}

void Board::save(std::string &path) {
    std::ofstream outFile(path);
    if (!outFile.is_open()) {
        std::cout << "Error" << std::endl;
        return;
    }

    for (const int id: figureOrder) {
        outFile << figures[id - 1]->getInfo() << std::endl;
    }

    outFile.close();
}


void Board::load(std::string &path) {
    figureOrder.clear();
    figures.clear();
    std::ifstream inFile(path);
    std::string line;

    if (!inFile.is_open()) {
        std::cerr << "Error " << std::endl;
    }

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        int id, arg1, arg2, arg3, arg4;
        std::string shape, option, color;

        if (!(iss >> id >> shape >> option >> color >> arg1 >> arg2 >> arg3)) {
            std::cout << "Error" << std::endl;
            continue;
        }
        if (iss >> arg4) {
                add(shape, option, color, arg1, arg2, arg3, arg4);
        }
        else {
            add(shape, option, color, arg1, arg2, arg3);
        }
    }

    inFile.close();
}


void Board::shapes() {
    std::cout << "triangle x, y, height" << std::endl << "circle x, y, radius" << std::endl << "square x, y, height" << std::endl << "line x0, y0, x1, y1" << std::endl;
}

void Board::select(int id) {
    if (id > 0 && id <= figures.size() && figures[id - 1] != nullptr) {
        std::cout << figures[id - 1]->getInfo() << std::endl;
        selected_id = id;
        if (figures[selected_id - 1] -> is_filled) figures[selected_id - 1] -> fill_draw(grid, '*');
        else figures[selected_id - 1] -> frame_draw(grid, '*');
        auto it = std::find(figureOrder.begin(), figureOrder.end(), id);
        if (it != figureOrder.end()) {
            figureOrder.erase(it);
            figureOrder.push_back(id);
        }
    }
    else {
        std::cout << "Something wrong with enetered id" << std::endl;
    }
}

void Board::select(int x, int y) {
    if (grid->grid[x][y].id != 0) {
        select(grid->grid[x][y].id);
    }
    else {
        std::cout << "Sorry, shape is not found by these coordinates" << std::endl;
    }
}

void Board::remove() {
    if (selected_id == 0 || !figures[selected_id]) {
        std::cout << "No figure was selected" << std::endl;
        return;
    }
    std::shared_ptr<Figure> removed_figure = figures[selected_id - 1];
    if (removed_figure -> is_filled) removed_figure -> fill_draw(grid, ' ');
    else removed_figure -> frame_draw(grid, ' ');
    figures[selected_id - 1] = nullptr;
    auto it = std::find(figureOrder.begin(), figureOrder.end(), selected_id);
    if (it != figureOrder.end()) {
        figureOrder.erase(it);
    }

    for (const auto& figure: figures) {
        if (figure) {
            if (figure->is_filled) figure->fill_draw(grid, '*');
            else figure->frame_draw(grid, '*');
        }
    }
}

void Board::paint(const std::string &color) {
    if (selected_id == 0 || !figures[selected_id]) {
        std::cout << "No figure was selected" << std::endl;
        return;
    }

    std::shared_ptr<Figure> selected_figure = figures[selected_id - 1];
    selected_figure->color = color;
}

void Board::edit(int dimension) {
    if (selected_id == 0 || !figures[selected_id]) {
        std::cout << "No figure was selected" << std::endl;
        return;
    }

    std::shared_ptr<Figure> selected_figure = figures[selected_id - 1];

    if (selected_figure -> is_filled) selected_figure -> fill_draw(grid, ' ');
    else selected_figure -> frame_draw(grid, ' ');

    if (auto* circle = dynamic_cast<Circle*>(selected_figure.get())) {
        circle->edit_dimension(dimension);
    } else if (auto* triangle = dynamic_cast<Triangle*>(selected_figure.get())) {
        triangle->edit_dimension(dimension);
    } else if (auto* square = dynamic_cast<Square*>(selected_figure.get())) {
        square->edit_dimension(dimension);
    }
    else std::cout << "Something wrong with parameters" << std::endl;

    for (const auto& figure: figures) {
        if (figure) {
            if (figure->is_filled) figure->fill_draw(grid, '*');
            else figure->frame_draw(grid, '*');
        }
    }
    if (selected_figure -> is_filled) selected_figure -> fill_draw(grid, '*');
    else selected_figure -> frame_draw(grid, '*');
}

void Board::edit(int d1, int d2) {
    if (selected_id == 0 || !figures[selected_id]) {
        std::cout << "No figure was selected" << std::endl;
        return;
    }

    std::shared_ptr<Figure> selected_figure = figures[selected_id - 1];

    if (selected_figure -> is_filled) selected_figure -> fill_draw(grid, ' ');
    else selected_figure -> frame_draw(grid, ' ');

    if (auto* line = dynamic_cast<Line*>(selected_figure.get())) line -> edit_dimension(d1, d2);
    else std::cout << "Something wrong with parameters" << std::endl;

    for (const auto& figure: figures) {
        if (figure) {
            if (figure->is_filled) figure->fill_draw(grid, '*');
            else figure->frame_draw(grid, '*');
        }
    }
    if (selected_figure -> is_filled) selected_figure -> fill_draw(grid, '*');
    else selected_figure -> frame_draw(grid, '*');
}

void Board::move(int x, int y) {
    if (selected_id == 0 || !figures[selected_id]) {
        std::cout << "No figure was selected" << std::endl;
        return;
    }

    std::shared_ptr<Figure> selected_figure = figures[selected_id - 1];

    if (selected_figure -> is_filled) selected_figure -> fill_draw(grid, ' ');
    else selected_figure -> frame_draw(grid, ' ');

    if (auto* circle = dynamic_cast<Circle*>(selected_figure.get())) {
        circle -> move(x, y);
    } else if (auto* triangle = dynamic_cast<Triangle*>(selected_figure.get())) {
        triangle -> move(x, y);
    } else if (auto* square = dynamic_cast<Square*>(selected_figure.get())) {
        square -> move(x, y);
    }
    else std::cout << "Something wrong with parameters" << std::endl;

    for (const auto& figure: figures) {
        if (figure) {
            if (figure->is_filled) figure->fill_draw(grid, '*');
            else figure->frame_draw(grid, '*');
        }
    }
    if (selected_figure -> is_filled) selected_figure -> fill_draw(grid, '*');
    else selected_figure -> frame_draw(grid, '*');
}


void Board::move(int d1, int d2, int d3, int d4) {
    if (selected_id == 0 || !figures[selected_id]) {
        std::cout << "No figure was selected" << std::endl;
        return;
    }
    std::shared_ptr<Figure> selected_figure = figures[selected_id - 1];

    if (selected_figure -> is_filled) selected_figure -> fill_draw(grid, ' ');
    else selected_figure -> frame_draw(grid, ' ');

    if (auto* line = dynamic_cast<Line*>(selected_figure.get())) line -> move(d1, d2, d3, d4);
    else std::cout << "Something wrong with parameters" << std::endl;

    for (const auto& figure: figures) {
        if (figure) {
            if (figure->is_filled) figure->fill_draw(grid, '*');
            else figure->frame_draw(grid, '*');
        }
    }
    if (selected_figure -> is_filled) selected_figure -> fill_draw(grid, '*');
    else selected_figure -> frame_draw(grid, '*');
}


