#include <iostream>
#include "BufferedReader.h"
#include "BufferedWriter.h"
#include "Shape.h"
#include <vector>
#include <sstream>
#include "SVGCanvas.h"

std::vector<Shape> parseShapes(BufferedReader &br) {
    std::vector<Shape> shapes;
    std::string line, word;
    while (br.ready()) {
        br >> line;
        line = trim(line);
        if (line.starts_with("#")) {
            continue;
        }
        std::istringstream stream(line);
        Shape shape;
        for (bool first = true; stream >> word; first = false) {
            if (first) {
                if (word == LINE_NAME) {
                    shape.shapeType = ShapeType::LINE;
                    shape.name = LINE_NAME;
                } else if (word == CIRCLE_NAME) {
                    shape.shapeType = ShapeType::CIRCLE;
                    shape.name = CIRCLE_NAME;
                } else if (word == RECT_NAME) {
                    shape.shapeType = ShapeType::RECT;
                    shape.name = RECT_NAME;
                } else if (word == ROTATE_NAME) {
                    shape.shapeType = ShapeType::ROTATE;
                    shape.name = ROTATE_NAME;
                } else if (word == TRANSLATE_NAME) {
                    shape.shapeType = ShapeType::TRANSLATE;
                    shape.name = TRANSLATE_NAME;
                } else if (word == SCALE_NAME) {
                    shape.shapeType = ShapeType::SCALE;
                    shape.name = SCALE_NAME;
                } else {
                    throw std::runtime_error("Line \"" + line + "\" is not valid - Invalid shape type");
                }
            } else {
                try {
                    shape.values.push_back(word);
                } catch (std::exception &) {
                    throw std::runtime_error("Line \"" + line + "\" is not valid - Invalid number format");
                }
            }
        }
        shapes.push_back(shape);
    }
    return shapes;
}


int main(int argv, char **argc) {
    if (argv != 4) {
        std::cout << "Program needs exactly three parameters." << std::endl;
        return EXIT_FAILURE;
    }
    try {
        std::string inputFile = argc[1];
        std::string outputFile = argc[2];
        std::string resolution = argc[3];
        BufferedReader br(inputFile);
        BufferedWriter bw(outputFile);
        auto shapes = parseShapes(br);

        SVGCanvas canvas(resolution);
        auto content = canvas.draw(shapes);
        bw << content;
        std::cout << "OK" << std::endl;
        std::cout << shapes.size() << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
