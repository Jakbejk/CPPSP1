#pragma once


#include <cmath>
#include <string>

class Position {
public:
    explicit Position(double x, double y) {
        this->x = x;
        this->y = y;
    }

    void rotate(const Position &other, double f) {
        *this -= other;
        double nx = this->x;
        double ny = this->y;
        double nf = f * atan(1) * 4 / 180;
        this->x = nx * cos(nf) - ny * sin(nf);
        this->y = nx * sin(nf) + ny * cos(nf);
        *this += other;
    }

    void translate(const Position &other) {
        *this += other;
    }

    void scale(const Position &other, double s) {
        auto copy = Position(this->x, this->y);
        copy -= other;
        copy *= s;
        copy += other;
        this->x = copy.x;
        this->y = copy.y;
    }

    Position operator+(const Position &other) const {
        return Position(this->x + other.x, this->y + other.y);
    }

    Position operator-(const Position &other) const {
        return Position(this->x - other.x, this->y - other.y);
    }

    Position operator*(double f) const {
        return Position(this->x * f, this->y * f);
    }

    void operator*=(double f) {
        this->x *= f;
        this->y *= f;
    }

    void operator+=(const Position &other) {
        this->x += other.x;
        this->y += other.y;
    }

    void operator-=(const Position &other) {
        this->x -= other.x;
        this->y -= other.y;
    }

    bool operator==(const Position &other) const {
        return this->x == other.x && this->y == other.y;
    }

    double getX() const {
        return this->x;
    }

    double getY() const {
        return this->y;
    }

private:
    double x;
    double y;

};