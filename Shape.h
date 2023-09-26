#pragma once

#include <iostream>
#include <vector>

constexpr std::string_view LINE_NAME = "line";
constexpr std::string_view ROTATE_NAME = "rotate";
constexpr std::string_view TRANSLATE_NAME = "translate";
constexpr std::string_view CIRCLE_NAME = "circle";
constexpr std::string_view RECT_NAME = "rect";
constexpr std::string_view SCALE_NAME = "scale";


enum class ShapeType {
    UNKNOWN, ROTATE, TRANSLATE, SCALE, RECT, CIRCLE, LINE
};

struct Shape {
public:
    std::vector<std::string> values;
    std::string name = "<UNKNOWN>";
    ShapeType shapeType = ShapeType::UNKNOWN;
};



