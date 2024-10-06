#pragma once

#include <memory>

#include "Grid.h"

class Figure {
public:
    bool is_filled;
    int id;
    virtual ~Figure() = default;
    virtual void frame_draw(std::shared_ptr<Grid>& grid, char symbol) = 0;
    virtual void fill_draw(std::shared_ptr<Grid>& grid, char symbol) = 0;
    virtual std::string getInfo() = 0;
    virtual bool isSameFigure(std::shared_ptr<Figure>& other) = 0;
    Figure(bool filled, int id) : is_filled(filled), id(id) {}
};

class Triangle: public Figure {
    int x;
    int y;
    int height;
    std::string color;
public:
    Triangle(int x, int y, int height, std::string color, const bool is_filled, const int id): Figure(is_filled, id), x(x), y(y), height(height), color(color){}
    void frame_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    void fill_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    std::string getInfo() override;
    bool isSameFigure(std::shared_ptr<Figure>& other) override;
};

class Circle: public Figure {
    int x;
    int y;
    int radius;
    std::string color;
public:
    Circle(int x, int y, int height, std::string color, bool is_filled, const int id): Figure(is_filled, id), x(x), y(y), radius(height), color(std::move(color)){}
    void frame_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    void fill_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    std::string getInfo() override;
    bool isSameFigure(std::shared_ptr<Figure>& other) override;
};


class Square: public Figure {
    int x;
    int y;
    int height;
    std::string color;
public:
    Square(int x, int y, int height, std::string color, bool is_filled, const int id): Figure(is_filled, id), x(x), y(y), height(height), color(std::move(color)){}
    void frame_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    void fill_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    std::string getInfo() override;
    bool isSameFigure(std::shared_ptr<Figure>& other) override;
};


class Line: public Figure {
    int x0;
    int y0;
    int x1;
    int y1;
    std::string color;
public:
    Line(int x, int y, int v, int w, std::string color, bool is_filled, const int id): Figure(is_filled, id), x0(x), y0(y), x1(v), y1(w), color(std::move(color)) {}
    void frame_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    void fill_draw(std::shared_ptr<Grid>& grid, char symbol) override;
    std::string getInfo() override;
    bool isSameFigure(std::shared_ptr<Figure>& other) override;
};