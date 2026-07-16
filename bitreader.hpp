#ifndef BITREADER_HPP
#define BITREADER_HPP

#include<fstream>
class BitReader {
private:
    std::ifstream& in;
    unsigned char buffer;
    int bitCount;

public:
    BitReader(std::ifstream& inputStream);

    bool readBit(bool& bit);
};



#endif