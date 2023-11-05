#pragma once

#include "Canvas.h"
#include <array>
#include "Position.h"


class PmgCanvas : public Canvas {
private:
    static std::vector<Position> getCircle(const Shape &shape) {
        if (shape.shapeType == ShapeType::CIRCLE) {
            checkCircleArgs(shape.values);
            double x, y, r;
            x = std::stod(shape.values[0]);
            y = std::stod(shape.values[1]);
            r = std::stod(shape.values[2]);
            std::vector<Position> result;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < r; j++) {
                    if (i * i + j * j <= r * r && (i + 1) * (i + 1) + j * j > r * r) {
                        result.emplace_back(x + i, y + j);
                        result.emplace_back(x - i, y + j);
                        result.emplace_back(x + i, y - j);
                        result.emplace_back(x - i, y - j);
                    }
                }
            }
            return result;
        }
        return std::vector<Position>{};
    }

    static std::vector<Position> getRect(const Shape &shape) {
        if (shape.shapeType == ShapeType::RECT) {
            checkRectArgs(shape.values);
            double x, y;
            double width, height;
            x = std::stod(shape.values[0]);
            y = std::stod(shape.values[1]);
            width = std::stod(shape.values[2]);
            height = std::stod(shape.values[3]);
            std::vector<Position> result;

            auto a = getLine(x, y, x + width, y);
            auto b = getLine(x + width, y, x + width, y + height);
            auto c = getLine(x + width, y + height, x, y + height);
            auto d = getLine(x, y + height, x, y);
            result.insert(result.end(), a.begin(), a.end());
            result.insert(result.end(), b.begin(), b.end());
            result.insert(result.end(), c.begin(), c.end());
            result.insert(result.end(), d.begin(), d.end());
            return result;
        }
        return std::vector<Position>{};
    }

    static std::vector<Position> getLine(double x1, double y1, double x2, double y2) {
        std::vector<Position> result;

        double dx = x2 - x1;
        double dy = y2 - y1;

        double length = sqrt(dx * dx + dy * dy);

        double x = x1;
        double y = y1;

        double stepX = dx / length;
        double stepY = dy / length;

        for (int i = 0; i < length; i++) {
            result.emplace_back(x, y);
            x += stepX;
            y += stepY;
        }
        return result;
    }

    static std::vector<Position> getLine(const Shape &shape) {
        if (shape.shapeType == ShapeType::LINE) {
            checkLineArgs(shape.values);
            try {
                double x1, y1;
                double x2, y2;
                x1 = std::stod(shape.values[0]);
                y1 = std::stod(shape.values[1]);
                x2 = std::stod(shape.values[2]);
                y2 = std::stod(shape.values[3]);
                return getLine(x1, y1, x2, y2);
            } catch (std::exception &e) {
                std::cerr << "Error in method getLine: " << e.what() << std::endl;
                return std::vector<Position>{};
            }
        }
        return std::vector<Position>{};
    }

    static std::vector<Position> getPmg(const Shape &shape) {
        std::vector<Position> result;
        auto a = getLine(shape);
        auto b = getCircle(shape);
        auto c = getRect(shape);
        result.insert(result.end(), a.begin(), a.end());
        result.insert(result.end(), b.begin(), b.end());
        result.insert(result.end(), c.begin(), c.end());
        return result;
    }

    static std::vector<Position> rotate(const std::vector<Position> &raster, const Shape &shape) {
        checkRotateArgs(shape.values);
        std::vector<Position> calculated;
        double x, y, delta;
        x = std::stod(shape.values[0]);
        y = std::stod(shape.values[1]);
        delta = std::stod(shape.values[2]);
        for (auto position: raster) {
            position.rotate(Position(x, y), delta);
            calculated.push_back(position);
        }
        return calculated;
    }

    static std::vector<Position> translate(const std::vector<Position> &raster, const Shape &shape) {
        checkTranslateArgs(shape.values);
        std::vector<Position> calculated;
        double x, y;
        x = std::stod(shape.values[0]);
        y = std::stod(shape.values[1]);
        for (auto position: raster) {
            position.translate(Position(x, y));
            calculated.push_back(position);
        }
        return calculated;
    }

    static std::vector<Position> scale(const std::vector<Position> &raster, const Shape &shape) {
        checkScaleArgs(shape.values);
        std::vector<Position> calculated;
        double x, y, s;
        x = std::stod(shape.values[0]);
        y = std::stod(shape.values[1]);
        s = std::stod(shape.values[2]);
        for (auto position: raster) {
            position.scale(Position(x, y), s);
            calculated.push_back(position);
        }
        return calculated;
    }

public:
    explicit PmgCanvas(const std::string &size) : Canvas(size) {

    }

    std::string draw(const std::vector<Shape> &shapes) override {
        std::vector<Position> positionRaster;
        std::string pgm;
        pgm += "P2\n";
        pgm.append(std::to_string(this->width) + " " + std::to_string(this->height) + "\n");
        pgm += "1\n";
        std::vector<std::vector<bool>> raster(this->width, std::vector<bool>(this->height, true));
        for (auto const &shape: shapes) {
            if (shape.shapeType == ShapeType::ROTATE) {
                positionRaster = rotate(positionRaster, shape);
            } else if (shape.shapeType == ShapeType::TRANSLATE) {
                positionRaster = translate(positionRaster, shape);
            } else if (shape.shapeType == ShapeType::SCALE) {
                positionRaster = scale(positionRaster, shape);
            } else {
                for (auto const &pos: getPmg(shape)) {
                    positionRaster.push_back(pos);
                }
            }
        }
        for (const auto &pos: positionRaster) {
            if (pos.getX() >= 0 && std::round(pos.getX()) < (int) this->width && pos.getY() >= 0 &&
                pos.getY() < (int) this->height) {
                raster[(int) pos.getX()][(int) pos.getY()] = false;
            }
        }
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                pgm += std::to_string(raster[j][i]) + " ";
            }
            pgm += "\n";
        }
        return pgm;
    }
};
