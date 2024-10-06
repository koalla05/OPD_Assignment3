#include <iostream>
#include <sstream>

#include "Board.h"

void proccessCommand(std::string& input, const std::shared_ptr<Board>& board) {
    std::istringstream iss(input);
    std::string command;
    iss >> command;

    if (command == "draw") {
        board -> print();
    }
    else if (command == "list"){
        board -> list();
    }
    else if (command == "shapes") {
        board -> shapes();
    }
    else if (command == "undo") {
        board -> undo();
    }
    else if (command == "clear") {
        board -> clear();
    }
    else if (command == "save") {
        std::string path;
        iss >> path;
        board -> save(path);
    }
    else if (command == "load") {
        std::string path;
        iss >> path;
        board -> load(path);
    }
    else if (command == "add") {
        std::string shape, option, color;
        int arg1, arg2, arg3, arg4;

        if (!(iss >> shape >> option >> color >> arg1 >> arg2 >> arg3)) {
            std::cout << "Error: Invalid input for shape and arguments!" << std::endl;
            return;
        }
        if (iss >> arg4) {
            board -> add(shape, option, color, arg1, arg2, arg3, arg4);
        }
        else {
            board -> add(shape, option, color, arg1, arg2, arg3);
        }
    }
    else {
        std::cout << "You are stupid" << std::endl;
    }

}



int main() {
    std::shared_ptr<Board> board = std::make_shared<Board>();    std::string input;
    std::string triangle = "triangle";
    std::string line = "line";
    std::string square = "square";
    std::string circle = "circle";
    std::string frame = "frame";
    std::string fill = "fill";
    std::string red = "red";
    std::string green = "green";
    std::string cyan = "cyan";
    std::string color = "color";
    board->add(circle, fill, green, 10, 10, 5);
    board->add(circle, frame, red, 20, 10, 5);

    board->add(square, frame, cyan, 0, 0, 5);
    board->add(triangle, fill, color, 10, 1, 7);
    // board->add(triangle, 10, 1, 7);
    // board->add(line, 5, 10, 30, 80);
    // board->add(line, 5, 10, 30, 80);
    // board->add(triangle, 25, 10, 3);
    // board->add(square, 15, 15, 30);
    // board->add(square, 15, 15, 30);
    // board->add(triangle, 19, 5, 10);
    // board->add(line, 0, 1, 9, 4);
    board->print();
    std::cout << "--------------------------------------------------" << std::endl;
    board -> list();
    //
    // std::string path = "test.txt";
    // board->save(path);
    // board->undo();
    // board->print();
    // std::cout << "--------------------------------------------------" << std::endl;
    //
    // board->list();
    // std::cout << "--------------------------------------------------" << std::endl;
    //
    //
    // board->clear();
    // board->print();
    // std::cout << "--------------------------------------------------" << std::endl;
    //
    // board->load(path);
    // board->print();
    // std::cout << "--------------------------------------------------" << std::endl;

    while (true) {
        std::cout << "Please, enter what you want to do: " << std::endl;
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }
        proccessCommand(input, board);
    }
    return 0;
}
