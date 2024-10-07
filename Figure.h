#pragma once

#include <memory>
#include <utility>

#include "Grid.h"

class Figure {
public:
    bool is_filled;
    int id;
    std::string color;
    virtual ~Figure() = default;
    virtual void frame_draw(std::shared_ptr<Grid>& grid, char symbol) = 0;
    virtual void fill_draw(std::shared_ptr<Grid>& grid, char symbol) = 0;
    virtual std::string getInfo() = 0;
    virtual bool isSameFigure(std::shared_ptr<Figure>& other) = 0;
    Figure(bool filled, int id, std::string color) : is_filled(filled), id(id), color(std::move(color)) {}
};

class Triangle: public Figure {
    int x;
    int y;
    int height;
public:
    Triangle(int x, int y, int height, std::string color, const bool is_filled, const int id): Figure(is_filled, id, std::move(color)), x(x), y(y), height(height){}
    void frame_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    void fill_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    std::string getInfo() override;
    bool isSameFigure(std::shared_ptr<Figure>& other) override;
    void edit_dimension(int dimension);
    void move(int d1, int d2);
};

class Circle: public Figure {
    int x;
    int y;
    int radius;
public:
    Circle(int x, int y, int height, std::string color, bool is_filled, const int id): Figure(is_filled, id, color), x(x), y(y), radius(height){}
    void frame_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    void fill_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    std::string getInfo() override;
    bool isSameFigure(std::shared_ptr<Figure>& other) override;
    void edit_dimension(int dimension);
    void move(int d1, int d2);
};


class Square: public Figure {
    int x;
    int y;
    int height;
public:
    Square(int x, int y, int height, std::string color, bool is_filled, const int id): Figure(is_filled, id, color), x(x), y(y), height(height){}
    void frame_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    void fill_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    std::string getInfo() override;
    bool isSameFigure(std::shared_ptr<Figure>& other) override;
    void edit_dimension(int dimension);
    void move(int d1, int d2);
};


class Line: public Figure {
    int x0;
    int y0;
    int x1;
    int y1;
public:
    Line(int x, int y, int v, int w, std::string color, bool is_filled, const int id): Figure(is_filled, id, color), x0(x), y0(y), x1(v), y1(w) {}
    void frame_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    void fill_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    std::string getInfo() override;
    bool isSameFigure(std::shared_ptr<Figure>& other) override;
    void edit_dimension(int d1, int d2);
    void move(int d1, int d2, int d3, int d4);
};