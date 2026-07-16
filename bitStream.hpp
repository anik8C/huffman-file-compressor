#ifndef BITSTREAM_HPP
#define BITSTREAM_HPP

#include <fstream>

class BitWriter {
private:
    std::ofstream& out;
    unsigned char buffer;
    int bitCount;

public:
    BitWriter(std::ofstream& outputStream);
    ~BitWriter();

    void writeBit(bool bit);
    void flush();
};

#endif