#pragma once

#include <iostream>
#include <sstream>

class Canvas {
protected:
    std::size_t width{};
    std::size_t height{};
public:
    explicit Canvas(const std::string &size) {
        std::string tmpSize;
        std::istringstream stream(size);
        if (std::getline(stream, tmpSize, 'x')) {
            width = std::stoi(tmpSize);
            std::getline(stream, tmpSize);
            height = std::stoi(tmpSize);
        } else {
            throw std::runtime_error("Must be format of XXxXX");
        }
    }


    virtual std::string draw(const std::vector<Shape> &shapes) = 0;
};