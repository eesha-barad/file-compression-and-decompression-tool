# file-compression-and-decompression-tool
## Overview
This project is a file compression and decompression tool implemented in C using the Huffman Coding algorithm. It efficiently compresses files by assigning shorter binary codes to frequently occurring characters, reducing the overall file size while ensuring lossless data recovery during decompression.

## Features
File Compression: Compresses input files using Huffman coding to reduce file size.
File Decompression: Restores the original content from a compressed file.
Single Source File: Both compression and decompression functionalities are implemented in a single source file for simplicity.
Ensures lossless data recovery.

## How It Works
### Compression Process:
Reads the input file and calculates the frequency of each character.
Constructs a Huffman Tree based on character frequencies.
Assigns binary codes to characters, with shorter codes for higher frequencies.
Encodes the file data using the Huffman codes.
Writes the compressed binary data and Huffman tree metadata to a new file.
### Decompression Process:
Reads the Huffman tree metadata from the compressed file header.
Reconstructs the Huffman Tree.
Decodes the binary data back into the original file content.
## How to Use
### Prerequisites
A C compiler (e.g., GCC).
Basic understanding of the command line.
### Compilation
Run the following command to compile the project:

bash
make
Or, compile directly with:

bash
gcc huffman.c -o huffman
Usage
To compress a file:

bash
Copy code
./huffman.c c <input_file> <output_file>
To decompress a file:

bash
Copy code
./huffman.c d <compressed_file> <output_file>
### Example
Compress input.txt:
bash
./huffman.c c input.txt compressed.bin
Decompress compressed.bin:
bash
./huffman.c d compressed.bin decompressed.txt

## Technical Details
Algorithm: Huffman Coding
Data Structures:
Min-Heap for tree construction.
Binary Tree for encoding/decoding.
File Header: Encodes the Huffman tree metadata to enable decompression.

## Testing
Test the tool with sample files in the data directory.
Verify that the decompressed file matches the original input file.

## Future Improvements
Support for multi-threaded compression for large files.
Add error handling for invalid inputs or corrupted files.
Improve efficiency for handling large datasets.

## Acknowledgments
Implementation based on standard Huffman coding principles.
Inspired by tutorials and open-source repositories on Huffman coding.
