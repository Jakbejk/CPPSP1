#pragma once

#include "Canvas.h"
#include <map>
#include "Shape.h"
#include "Utils.h"
#include <functional>

struct SVGShape {
    std::map<std::string, std::string> attributes;
    std::string name = "<UNKNOWN>";
    ShapeType shapeType = ShapeType::UNKNOWN;
    std::vector<SVGShape> children;
};

class SVGCanvas : public Canvas {
private :
    std::vector<SVGShape> svgShapes;

    static void
    addRelation(const std::function<void(SVGShape &)> &addParent, const std::function<void(SVGShape &)> &addSibling,
                SVGShape &svgShape) {
        if (svgShape.shapeType == ShapeType::CIRCLE
            || svgShape.shapeType == ShapeType::RECT
            || svgShape.shapeType == ShapeType::LINE) {
            addSibling(svgShape);
        } else {
            addParent(svgShape);
        }
    }

    void formSvgStructure(const std::vector<Shape> &shapes) {
        for (Shape shape: shapes) {
            SVGShape svgShape;
            svgShape.shapeType = shape.shapeType;
            svgShape.name = shape.name;
            if (shape.shapeType == ShapeType::LINE) {
                if (shape.values.size() == 4) {
                    svgShape.attributes["x1"] = shape.values[0];
                    svgShape.attributes["y1"] = shape.values[1];
                    svgShape.attributes["x2"] = shape.values[2];
                    svgShape.attributes["y2"] = shape.values[3];
                    svgShape.attributes["fill"] = "#000000";
                    svgShape.attributes["stroke"] = "#000000";
                    svgShape.attributes["stroke-width"] = "2";
                    if (!isRealNumber(svgShape.attributes["x1"]) ||
                        !isRealNumber(svgShape.attributes["x2"]) ||
                        !isRealNumber(svgShape.attributes["y1"]) ||
                        !isRealNumber(svgShape.attributes["y2"])) {
                        throw std::runtime_error("Line contains wring data - x1 || x2 || y1 || y2 is not real number");
                    }
                    if (std::stod(svgShape.attributes["x1"]) == std::stod(svgShape.attributes["x2"]) &&
                        std::stod(svgShape.attributes["y1"]) == std::stod(svgShape.attributes["y1"])) {
                        throw std::runtime_error("Line contains wrong data - x1 == x2 && y1 == y2.");
                    }
                } else {
                    throw std::runtime_error("Line should have exactly four parameters.");
                }
            } else if (shape.shapeType == ShapeType::CIRCLE) {
                if (shape.values.size() == 3) {
                    svgShape.attributes["cx"] = shape.values[0];
                    svgShape.attributes["cy"] = shape.values[1];
                    svgShape.attributes["r"] = shape.values[2];
                    svgShape.attributes["fill"] = "none";
                    svgShape.attributes["stroke"] = "#000000";
                    svgShape.attributes["stroke-width"] = "2";
                    std::stod(svgShape.attributes["cx"]);
                    std::stod(svgShape.attributes["cy"]);
                    if (!isRealNumber(svgShape.attributes["cx"]) ||
                        !isRealNumber(svgShape.attributes["cy"]) ||
                        !isRealNumber(svgShape.attributes["r"])) {
                        throw std::runtime_error("Circle contains wrong data - cx || cy || r is not real number.");
                    } else if (std::stod(svgShape.attributes["r"]) <= 0) {
                        throw std::runtime_error("Circle contains wrong data - r <= 0.");
                    }
                } else {
                    throw std::runtime_error("Circle should have exactly three parameters.");
                }
            } else if (shape.shapeType == ShapeType::RECT) {
                if (shape.values.size() == 4) {
                    svgShape.attributes["x"] = shape.values[0];
                    svgShape.attributes["y"] = shape.values[1];
                    svgShape.attributes["width"] = shape.values[2];
                    svgShape.attributes["height"] = shape.values[3];
                    svgShape.attributes["fill"] = "none";
                    svgShape.attributes["stroke"] = "#000000";
                    svgShape.attributes["stroke-width"] = "2";
                    if (!isRealNumber(svgShape.attributes["x"]) ||
                        !isRealNumber(svgShape.attributes["y"]) ||
                        !isRealNumber(svgShape.attributes["width"]) ||
                        !isRealNumber(svgShape.attributes["height"])) {
                        throw std::runtime_error(
                                "Rect contains wrong data - x || y || width || height is not real number.");
                    } else if (std::stod(svgShape.attributes["width"]) <= 0 ||
                               std::stod(svgShape.attributes["height"]) <= 0) {
                        throw std::runtime_error("Rect contains wrong data - width <= 0 || height <= 0.");
                    }
                } else {
                    throw std::runtime_error("Rect should have exactly four parameters.");
                }
            } else if (shape.shapeType == ShapeType::TRANSLATE) {
                if (shape.values.size() == 2) {
                    svgShape.name = "g";
                    svgShape.attributes["transform"] = stringFormat("translate(%s, %s)",
                                                                    shape.values[0].c_str(),
                                                                    shape.values[1].c_str());
                    if (!isRealNumber(shape.values[0]) ||
                        !isRealNumber(shape.values[1])) {
                        throw std::runtime_error("translate contains wrong data - x || y is not real number.");
                    }
                } else {
                    throw std::runtime_error("translate should have exactly two parameters.");
                }
            } else if (shape.shapeType == ShapeType::ROTATE) {
                if (shape.values.size() == 3) {
                    svgShape.name = "g";
                    svgShape.attributes["transform"] = stringFormat("rotate(%s, %s, %s)",
                                                                    shape.values[2].c_str(),
                                                                    shape.values[0].c_str(),
                                                                    shape.values[1].c_str());
                    if (!isRealNumber(shape.values[0]) ||
                        !isRealNumber(shape.values[1]) ||
                        !isRealNumber(shape.values[2])) {
                        throw std::runtime_error("rotate contains wrong data - x || y || a is not real number.");
                    }
                } else {
                    throw std::runtime_error("rotate should have exactly three parameters.");
                }
            } else if (shape.shapeType == ShapeType::SCALE) {
                if (shape.values.size() == 3) {
                    svgShape.name = "g";
                    svgShape.attributes["transform"] = stringFormat("translate(%s, %s) scale(%s)",
                                                                    shape.values[0].c_str(),
                                                                    shape.values[1].c_str(),
                                                                    shape.values[2].c_str());
                    if (!isRealNumber(shape.values[0]) ||
                        !isRealNumber(shape.values[1]) ||
                        !isRealNumber(shape.values[2])) {
                        throw std::runtime_error("scale contains wrong data - x || y || f is not real number.");
                    }
                } else {
                    throw std::runtime_error("scale should have exactly three parameters.");
                }
            } else {
                throw std::runtime_error("Unknown Shape type \"" + shape.name + "\".");
            }
            addRelation([this](SVGShape &shape) {
                            for (const SVGShape &child: this->svgShapes) {
                                shape.children.push_back(child);
                            }
                            this->svgShapes.clear();
                            this->svgShapes.push_back(shape);
                        },
                        [this](SVGShape &shape) {
                            this->svgShapes.push_back(shape);
                        }, svgShape);
        }
    };

    static void drawContent(std::string &content, const std::vector<SVGShape> &shapes, uint16_t level) {
        for (const SVGShape &svgShape: shapes) {
            for (int i = 0; i < level; i++) content += "\t";
            content += stringFormat("<%s", svgShape.name.c_str());
            for (auto const &[key, value]: svgShape.attributes) {
                content += stringFormat(" %s='%s'", key.c_str(), value.c_str());
            }
            if (svgShape.children.empty()) {
                content += "/>\n";
            } else {
                content += ">\n";
                drawContent(content, svgShape.children, level + 1);
                for (int i = 0; i < level; i++) content += "\t";
                content += stringFormat("</%s>\n", svgShape.name.c_str());
            }
        }
    }

public:
    std::string draw(const std::vector<Shape> &shapes) override {
        this->formSvgStructure(shapes);
        std::string content = stringFormat(
                "<svg xmlns='http://www.w3.org/2000/svg' width='%d' height='%d'>\n", this->width,
                this->height);
        drawContent(content, this->svgShapes, 1);
        content += "</svg>";
        return content;
    }

    explicit SVGCanvas(const std::string &size) : Canvas(size) {

    }
};