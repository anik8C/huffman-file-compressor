#include "bitreader.hpp"

BitReader::BitReader(std::ifstream& inputStream)
    : in(inputStream), buffer(0), bitCount(0) {}

bool BitReader::readBit(bool& bit) {

    if (bitCount == 0) {
        if (!in.read((char*)&buffer, 1))
            return false;
        bitCount = 8;
    }

    bit = (buffer & 0x80);   // extract MSB
    buffer <<= 1;
    bitCount--;

    return true;
}