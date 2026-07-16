# Huffman File Compression & Decompression System (C++ CLI)

##  Overview

This project is a command-line based **file compression and decompression utility** built entirely in **pure C++**. It implements the **Huffman Coding algorithm** to perform lossless data compression at the bit level.

The system is designed with a modular architecture and demonstrates concepts from:

* Data Structures (Trees, Priority Queue)
* Algorithms (Greedy Strategy – Huffman Coding)
* Systems Programming (Binary I/O, Bit Manipulation)
* File Format Design
* Command Line Interface (CLI) Development

This is not a toy implementation — it is a complete reversible compression engine with a custom binary file format.

---

# Features

* ✅ Lossless compression using Huffman Coding
* ✅ Bit-level writing and reading (manual bit packing)
* ✅ Custom binary file format
* ✅ Safe decompression using original file size tracking
* ✅ Command-line interface support
* ✅ Compression statistics output
* ✅ Modular code structure

---

# Project Architecture

```
File_Compressor/
│
├── main.cpp          (CLI logic + orchestration)
├── huffman.hpp       (Huffman class declarations)
├── huffman.cpp       (Tree construction + code generation)
├── bitstream.hpp     (BitWriter class)
├── bitstream.cpp     (Bit-level write implementation)
├── bitreader.hpp     (BitReader class)
├── bitreader.cpp     (Bit-level read implementation)
```

---

# How It Works

## 1️⃣ Compression Flow

1. Read input file in binary mode
2. Build frequency table (0–255 byte range)
3. Construct Huffman tree using a min-heap
4. Generate prefix-free binary codes
5. Write custom header
6. Encode file content bit-by-bit
7. Pack bits into bytes and write to output file

---

## 2️⃣ Decompression Flow

1. Read header metadata
2. Reconstruct frequency table
3. Rebuild Huffman tree
4. Read encoded bitstream
5. Traverse tree bit-by-bit
6. Stop after original byte count is restored

---

#  Custom File Format (.huff)

The compressed file uses a structured binary layout:

```
[Original File Size (int)]
[Number of Unique Characters (int)]
[Character (1 byte) + Frequency (int)] × N
[Encoded Bitstream]
```

This ensures decompression is deterministic and safe.

---

#  Usage

## Compile

```
g++ main.cpp huffman.cpp bitstream.cpp bitreader.cpp -o compressor
```

---

## Compress a File

```
./compressor -c input.txt output.huff
```

---

## 📂 Decompress a File

```
./compressor -d output.huff restored.txt
```

---

# Sample Output

```
Original Size: 5080 bytes
Compressed Size: 3077 bytes
Compression Saved: 39.4 %
Compression complete.
```

---

#  Testing Integrity

To verify decompression correctness:

On Windows:

```
cmd /c fc input.txt restored.txt
```

If no differences are reported → compression is lossless.

---

# Key Concepts Demonstrated

## Huffman Coding

* Greedy algorithm
* Prefix-free codes
* Optimal variable-length encoding

## Bit-Level Manipulation

* Manual bit shifting
* Byte buffering
* Padding handling

## Binary File I/O

* `std::ifstream` / `std::ofstream`
* `read()` and `write()` operations
* Stream position tracking using `tellp()`

## CLI Argument Parsing

* `argc` / `argv`
* Mode selection (-c / -d)
* Input validation

---

#  Limitations

* Static Huffman (not adaptive)
* No canonical encoding optimization
* No corruption detection (no magic number)
* Header size may reduce efficiency for very small files

---

# Possible Future Enhancements

* Add magic number for format validation
* Add canonical Huffman encoding
* Implement LZ77 + Huffman hybrid (ZIP-style compression)
* Add corruption detection
* Add progress indicator for large files
* Convert to cross-platform production CLI tool

---

# Compression Behavior

Compression efficiency depends on entropy:

* Text files → Good compression
* Repetitive data → Very good compression
* Random/encrypted data → Poor or negative compression

---

# Conclusion

This project demonstrates deep understanding of:

* Data compression theory
* Systems-level file handling
* Bitwise operations
* Algorithm implementation
* Clean modular C++ design

It serves as a strong portfolio project for systems programming and algorithm-focused roles.

---

# Author

Built as a deep systems programming project to master:

* Data structures
* Binary file formats
* CLI tool development
* Low-level C++ design

---

🔥 Mastery is built one system at a time.
