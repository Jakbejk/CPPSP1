#pragma once

#include <fstream>
#include <string>

class BufferedReader {
private:
    std::ifstream istream;

public:
    explicit BufferedReader(const std::string &name) {
        istream.open(name);
        if (!istream.is_open()) {
            throw std::runtime_error("Input stream can not be opened, check if file exists.");
        }
    }

    std::string readLine() {
        std::string buffer;
        std::getline(istream, buffer);
        return buffer;
    }

    friend std::ostream &operator<<(std::ostream &output, BufferedReader &reader) {
        output << reader.readLine();
        return output;
    }

    friend BufferedReader &operator>>(BufferedReader &br, std::string &buffer) {
        buffer = br.readLine();
        return br;
    }

    bool ready() const {
        return !istream.eof();
    }

    void close() {
        istream.close();
    }

    ~BufferedReader() {
        if (istream.is_open()) {
            istream.close();
        }
    }
};
