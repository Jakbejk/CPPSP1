#pragma once

#include <iostream>
#include <vector>
#include "Utils.h"

constexpr std::string_view LINE_NAME = "line";
constexpr std::string_view ROTATE_NAME = "rotate";
constexpr std::string_view TRANSLATE_NAME = "translate";
constexpr std::string_view CIRCLE_NAME = "circle";
constexpr std::string_view RECT_NAME = "rect";
constexpr std::string_view SCALE_NAME = "scale";

void checkTranslateArgs(const std::vector<std::string> &args) {
    if (args.size() != 2) {
        throw std::runtime_error("translate should have exactly two parameters");
    } else if (!isRealNumber(args[0])) {
        throw std::runtime_error("translate x is not an number.");
    } else if (!isRealNumber(args[1])) {
        throw std::runtime_error("translate y is not an number.");
    }
}

void checkRotateArgs(const std::vector<std::string> &args) {
    if (args.size() != 3) {
        throw std::runtime_error("Rotate should have exactly three parameters");
    } else if (!isRealNumber(args[0])) {
        throw std::runtime_error("Rotate x is not an number.");
    } else if (!isRealNumber(args[1])) {
        throw std::runtime_error("Rotate y is not an number.");
    } else if (!isRealNumber(args[2])) {
        throw std::runtime_error("Rotate r is not an number.");
    }
}

void checkScaleArgs(const std::vector<std::string> &args) {
    if (args.size() != 3) {
        throw std::runtime_error("Scale should have exactly three parameters");
    } else if (!isRealNumber(args[0])) {
        throw std::runtime_error("Scale x is not an number.");
    } else if (!isRealNumber(args[1])) {
        throw std::runtime_error("Scale y is not an number.");
    } else if (!isRealNumber(args[2])) {
        throw std::runtime_error("Scale s is not an number.");
    }
}


void checkRectArgs(const std::vector<std::string> &args) {
    if (args.size() != 4) {
        throw std::runtime_error("Rectangle should have exactly four parameters");
    } else if (!isRealNumber(args[0])) {
        throw std::runtime_error("Rectangle x is not an number.");
    } else if (!isRealNumber(args[1])) {
        throw std::runtime_error("Rectangle y is not an number.");
    } else if (!isRealNumber(args[2])) {
        throw std::runtime_error("Rectangle width is not an number.");
    } else if (!isRealNumber(args[3])) {
        throw std::runtime_error("Rectangle height is not an number.");
    } else if (std::stod(args[2]) <= 0 || std::stod(args[3]) <= 0) {
        throw std::runtime_error("Rectangle contains wrong data - width <= 0 && height <= 0.");
    }
}

void checkCircleArgs(const std::vector<std::string> &args) {
    if (args.size() != 3) {
        throw std::runtime_error("Circle should have exactly three parameters");
    } else if (!isRealNumber(args[0])) {
        throw std::runtime_error("Circle x is not an number.");
    } else if (!isRealNumber(args[1])) {
        throw std::runtime_error("Circle y is not an number.");
    } else if (!isRealNumber(args[2])) {
        throw std::runtime_error("Circle r is not an number.");
    } else if (std::stod(args[2]) <= 0) {
        throw std::runtime_error("Circle contains wrong data - r <= 0.");
    }
}

void checkLineArgs(const std::vector<std::string> &args) {
    if (args.size() != 4) {
        throw std::runtime_error("Line should have exactly four parameters");
    } else if (!isRealNumber(args[0])) {
        throw std::runtime_error("Line x1 is not an number.");
    } else if (!isRealNumber(args[1])) {
        throw std::runtime_error("Line y1 is not an number.");
    } else if (!isRealNumber(args[2])) {
        throw std::runtime_error("Line x2 is not an number.");
    } else if (!isRealNumber(args[3])) {
        throw std::runtime_error("Line y2 is not an number.");
    } else if (std::stod(args[0]) == std::stod(args[2]) &&
               std::stod(args[1]) == std::stod(args[3])) {
        throw std::runtime_error("Line contains wrong data - x1 == x2 && y1 == y2.");
    }
}


enum class ShapeType {
    UNKNOWN, ROTATE, TRANSLATE, SCALE, RECT, CIRCLE, LINE
};

struct Shape {
public:
    std::vector<std::string> values;
    std::string name = "<UNKNOWN>";
    ShapeType shapeType = ShapeType::UNKNOWN;
};



