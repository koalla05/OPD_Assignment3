#include "Board.h"
#include "Figure.h"
#include <fstream>
#include <iostream>
#include <sstream>

void Board::print() {
    for (const auto& row : grid->grid) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

void Board::add(std::string& shape, int x, int y, int height) {
    bool isSame = false;
    if (shape == "triangle") {
        std::shared_ptr<Figure> figure = std::make_shared<Triangle>(x, y, height);
        for (auto& element: figures) {
            if (element->isSameFigure(figure)) {
                isSame = true;
            }
        }
        if (!isSame) {
            figures.push_back(figure);
            figure->draw(grid, '*');
        }
        else {
            std::cout << "Such a figure already exists" << std::endl;
        }
    }
    else if (shape == "square") {
        std::shared_ptr<Figure> figure = std::make_shared<Square>(x, y, height);
        for (auto& element: figures) {
            if (element->isSameFigure(figure)) {
                isSame = true;
            }
        }
        if (!isSame) {
            figures.push_back(figure);
            figure->draw(grid, '*');
        }
        else {
            std::cout << "Such a figure already exists" << std::endl;
        }
    }
    else if (shape == "circle") {
        std::shared_ptr<Figure> figure = std::make_shared<Circle>(x, y, height);
        for (auto& element: figures) {
            if (element->isSameFigure(figure)) {
                isSame = true;
            }
        }
        if (!isSame) {
            figures.push_back(figure);
            figure->draw(grid, '*');
        }
        else {
            std::cout << "Such a figure already exists" << std::endl;
        }
    }
    else {
        std::cout << "Something is wrong with parameters" << std::endl;
    }
}

void Board::add(std::string& shape, int x0, int y0, int x1, int y1) {
    bool isSame = false;
    if (shape == "line") {
        std::shared_ptr<Figure> figure = std::make_shared<Line>(x0, y0, x1, y1);
        for (auto& element: figures) {
            if (element->isSameFigure(figure)) {
                isSame = true;
            }
        }
        if (!isSame) {
            figures.push_back(figure);
            figure->draw(grid, '*');
        }
        else {
            std::cout << "Such a figure already exists" << std::endl;
        }
    }
    else {
        std::cout << "Something is wrong with parameters" << std::endl;
    }
}


void Board::undo() {
    if (figures.empty()) {
        std::cout << "Sorry, no figures yet" << std::endl;
        return;
    }
    figures.back()->draw(grid, ' ');
    figures.pop_back();
    for (const auto& figure: figures) {
        figure->draw(grid, '*');
    }
}

void Board::clear() {
    while (!figures.empty()) {
        figures.back()->draw(grid, ' ');
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
        std::string shape;

        if (!(iss >> id >> shape >> arg1 >> arg2 >> arg3)) {
            std::cout << "Error" << std::endl;
            continue;
        }
        if (iss >> arg4) {
                add(shape, arg1, arg2, arg3, arg4);
        }
        else {
            add(shape, arg1, arg2, arg3);
        }
    }

    inFile.close();
}


void Board::shapes() {
    std::cout << "triangle x, y, height" << std::endl << "circle x, y, radius" << std::endl << "square x, y, height" << std::endl << "line x0, y0, x1, y1" << std::endl;
}
