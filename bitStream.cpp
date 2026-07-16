#include "bitstream.hpp"

BitWriter::BitWriter(std::ofstream& outputStream)
    : out(outputStream), buffer(0), bitCount(0) {}

BitWriter::~BitWriter() {
    flush();
}

void BitWriter::writeBit(bool bit) {
    buffer <<= 1;

    if (bit)
        buffer |= 1;

    bitCount++;

    if (bitCount == 8) {
        out.write((char*)&buffer, 1);
        buffer = 0;
        bitCount = 0;
    }
}

void BitWriter::flush() {
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        out.write((char*)&buffer, 1);
        buffer = 0;
        bitCount = 0;
    }
}