#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Figure.h"

class Board {
public:
    std::vector<std::shared_ptr<Figure>> figures;
    std::shared_ptr<Grid> grid;
    int selected_id = 0;
    Board() {
        grid = std::make_shared<Grid>();
    }

    void print();

    void add(std::string& shape, std::string& option, std::string& color, int x, int y, int height);
    void add(std::string& shape, std::string& option, std::string& color, int x0, int y0, int x1, int y1);

    void select(int id);
    void select(int x, int y);

    void remove();

    void undo();

    void clear();

    void list();

    void save(std::string &path);

    void load(std::string &path);

    void shapes();
};
