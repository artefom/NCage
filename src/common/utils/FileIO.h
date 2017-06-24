//
// Created by artef on 23.06.2017.
//

#ifndef PLAYIN_FILEIO_H
#define PLAYIN_FILEIO_H

#include <vector>
#include <fstream>

class FileIO {
public:
    static void read_file(const char *fname, std::vector<char> &buffer) {
        std::ifstream is(fname);
        if (!is.is_open()) {
            throw std::runtime_error("Could not open file " + std::string(fname));
        }
        while (!is.eof()) {
            buffer.push_back((char) is.get());
        }
        is.close();
    }
};


#endif //PLAYIN_FILEIO_H
