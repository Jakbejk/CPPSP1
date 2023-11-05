#pragma once

#include <fstream>

class BufferedWriter {
private:
    std::ofstream ostream;

public:
    explicit BufferedWriter(const std::string &name) : ostream(name) {
        if (!ostream.is_open()) {
            throw std::runtime_error("Output stream can not be opened.");
        }
    }

    void write(const std::string &content) {
        ostream << content;
    }

    void flush() {
        ostream.flush();
    }

    void close() {
        ostream.close();
    }

    friend BufferedWriter &operator<<(BufferedWriter &bw, const std::string &content) {
        bw.ostream << content;
        return bw;
    }

    ~BufferedWriter() {
        if (ostream.is_open()) {
            ostream.close();
        }
    }
};
