#include "Board.h"
#include "Figure.h"
#include <fstream>
#include <iostream>
#include <sstream>

void Board::print() {
    for (int i = 0; i < grid->BOARD_HEIGHT; ++i) {
        for (int j = 0; j < grid->BOARD_WIDTH; ++j) {
            const Cell& cell = grid->grid[i][j];
            if (cell.color == "red") {
                std::cout << "\033[31m" << cell.symbol << "\033[0m";
            } else if (cell.color == "green") {
                std::cout << "\033[32m" << cell.symbol << "\033[0m";
            } else if (cell.color == "blue") {
                std::cout << "\033[34m" << cell.symbol << "\033[0m";
            } else if (cell.color == "yellow") {
                std::cout << "\033[33m" << cell.symbol << "\033[0m";
            } else if (cell.color == "magenta") {
                std::cout << "\033[35m" << cell.symbol << "\033[0m";
            } else if (cell.color == "cyan") {
                std::cout << "\033[36m" << cell.symbol << "\033[0m";
            } else if (cell.color == "white") {
                std::cout << "\033[37m" << cell.symbol << "\033[0m";
            } else {
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
        std::cout << "Something wrong woth parameters" << std::endl;
    }

    if (shape == "triangle") {
        figure = std::make_shared<Triangle>(x, y, height, color, is_filled, figures.size());
    }
    else if (shape == "square") {
        figure = std::make_shared<Square>(x, y, height, color, is_filled, figures.size());
    }
    else if (shape == "circle") {
        figure = std::make_shared<Circle>(x, y, height, color, is_filled, figures.size());
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
        std::cout << "Something wrong woth parameters" << std::endl;
        return;
    }

    std::shared_ptr<Figure> figure;
    if (shape == "line") {
        figure = std::make_shared<Line>(x0, y0, x1, y1, color, is_filled, figures.size());
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
        if (figure->is_filled) figure->fill_draw(grid, color[0]);
        else {
            figure -> frame_draw(grid, color[0]);
            std::cout << "Frame";
        }
    }
    else {
        std::cout << "Such a figure already exists" << std::endl;
    }

}


void Board::undo() {
    if (figures.empty()) {
        std::cout << "Sorry, no figures yet" << std::endl;
        return;
    }
    std::shared_ptr<Figure> removed_figure = figures.back();

    if (removed_figure->is_filled) removed_figure->fill_draw(grid, ' ');
    else removed_figure->frame_draw(grid, ' ');
    figures.pop_back();

    for (const auto& figure: figures) {
        if (figure->is_filled) figure->fill_draw(grid, '*');
        else figure->frame_draw(grid, '*');
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
    for (int i = 0 ; i < figures.size(); ++i) {
        std::cout << figures[i] -> getInfo(i) << std::endl;
    }
}

void Board::save(std::string &path) {
    std::ofstream outFile(path);
    if (!outFile.is_open()) {
        std::cout << "Error" << std::endl;
        return;
    }

    for (int i = 0; i < figures.size(); ++i) {
        outFile << figures[i]->getInfo(i) << std::endl;
    }

    outFile.close();
}


void Board::load(std::string &path) {
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
