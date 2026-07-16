# File Compressor using Huffman Coding

A command-line file compression and decompression utility built in **C++** using the **Huffman Coding** algorithm. The project performs **lossless compression** by generating variable-length prefix codes based on character frequencies and stores the compressed output in a custom binary format.

## Features

- Lossless file compression and decompression
- Huffman Tree construction using a priority queue (min-heap)
- Custom binary file format for compressed data
- Bit-level encoding and decoding with manual bit packing
- Binary file I/O using C++ streams
- Compression statistics (original size, compressed size, compression ratio)
- Modular and object-oriented implementation

---

## Project Structure

```
File_Compressor/
│
├── main.cpp          # CLI entry point
├── huffman.hpp       # Huffman class declarations
├── huffman.cpp       # Tree construction and code generation
├── bitstream.hpp     # BitWriter interface
├── bitstream.cpp     # Bit-level writing
├── bitreader.hpp     # BitReader interface
├── bitreader.cpp     # Bit-level reading
```

---

## Working

### Compression

1. Read the input file in binary mode.
2. Calculate the frequency of each byte.
3. Build a Huffman Tree using a priority queue.
4. Generate variable-length Huffman codes.
5. Write metadata (header) to the output file.
6. Encode file contents and write compressed bits.

### Decompression

1. Read metadata from the compressed file.
2. Reconstruct the Huffman Tree.
3. Decode the compressed bitstream.
4. Restore the original file.

---

## Compressed File Format

```
[Original File Size]
[Number of Unique Characters]
[Character + Frequency] × N
[Encoded Bitstream]
```

The stored frequency table allows the Huffman Tree to be reconstructed during decompression.

---

## Build

```bash
g++ main.cpp huffman.cpp bitstream.cpp bitreader.cpp -o compressor
```

---

## Usage

### Compress

```bash
./compressor -c input.txt output.huff
```

### Decompress

```bash
./compressor -d output.huff restored.txt
```

---

## Sample Output

```
Original Size   : 5080 bytes
Compressed Size : 3077 bytes
Compression     : 39.4%
Compression completed successfully.
```

---

## Technologies Used

- C++
- STL
- Priority Queue
- Binary Trees
- Binary File I/O
- Bit Manipulation
- Object-Oriented Programming

---

## Future Improvements

- File format validation using a magic number
- Canonical Huffman Coding
- Corruption detection
- Support for larger files and streaming compression
- Multi-file or directory compression

---

## Learning Outcomes

This project strengthened my understanding of:

- Greedy algorithms
- Huffman Coding
- Binary file handling
- Bitwise operations
- Data serialization
- Modular software design
