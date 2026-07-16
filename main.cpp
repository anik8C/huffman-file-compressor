#include "huffman.hpp"
#include "bitstream.hpp"
#include "bitreader.hpp"

#include <fstream>
#include <iostream>
#include <vector>


void compress(const std::string& inputFile, const std::string& outputFile);
void decompress(const std::string& inputFile, const std::string& outputFile);

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cout << "Usage:\n";
        std::cout << "  -c input output   (compress)\n";
        std::cout << "  -d input output   (decompress)\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    if (mode == "-c") {
        compress(inputFile, outputFile);
    }
    else if (mode == "-d") {
        decompress(inputFile, outputFile);
    }
    else {
        std::cout << "Invalid option.\n";
        return 1;
    }

    return 0;
}

void compress(const std::string& inputFile, const std::string& outputFile) {

    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cout << "Error opening input file.\n";
        return;
    }

    std::vector<int> freq(256, 0);
    unsigned char ch;

    while (in.read((char*)&ch, 1)) {
        freq[ch]++;
    }

    int originalSize = 0;
    for (int i = 0; i < 256; i++)
        originalSize += freq[i];

    Huffman huff;
    huff.buildTree(freq);
    auto codes = huff.getCodes();

    in.clear();
    in.seekg(0);

    std::ofstream out(outputFile, std::ios::binary);

    // Write original file size
    out.write((char*)&originalSize, sizeof(int));

    // Count unique characters
    int unique = 0;
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            unique++;

    out.write((char*)&unique, sizeof(int));

    // Write (char, frequency)
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            unsigned char c = i;
            out.write((char*)&c, 1);
            out.write((char*)&freq[i], sizeof(int));
        }
    }

    BitWriter writer(out);

    while (in.read((char*)&ch, 1)) {
        std::string code = codes[ch];
        for (char bit : code) {
            writer.writeBit(bit == '1');
        }
    }

    writer.flush();
    std::streampos compressedSize = out.tellp();
    in.close();
    out.close();
    double ratio = 0.0;
    if (originalSize > 0)
        ratio = 100.0 * (1.0 - (double)compressedSize / originalSize);

    std::cout << "Original Size: " << originalSize << " bytes\n";
    std::cout << "Compressed Size: " << compressedSize << " bytes\n";
    std::cout << "Compression Saved: " << ratio << " %\n";
    std::cout << "Compression complete.\n";
}

void decompress(const std::string& inputFile, const std::string& outputFile) {

    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cout << "Error opening compressed file.\n";
        return;
    }

    std::ofstream out(outputFile, std::ios::binary);

    int originalSize;
    in.read((char*)&originalSize, sizeof(int));

    int unique;
    in.read((char*)&unique, sizeof(int));

    std::vector<int> freq(256, 0);

    for (int i = 0; i < unique; i++) {
        unsigned char c;
        int f;
        in.read((char*)&c, 1);
        in.read((char*)&f, sizeof(int));
        freq[c] = f;
    }

    Huffman huff;
    huff.buildTree(freq);
    Node* root = huff.getroot();

    BitReader reader(in);

    Node* curr = root;
    bool bit;
    int written = 0;

    while (written < originalSize && reader.readBit(bit)) {

        if (bit)
            curr = curr->right;
        else
            curr = curr->left;

        if (!curr->left && !curr->right) {
            out.write((char*)&curr->ch, 1);
            curr = root;
            written++;
        }
    }

    in.close();
    out.close();

    std::cout << "Decompression complete.\n";
}