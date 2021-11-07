# Assignment 5 - Huffman Coding

## Description of Program

In this assignment, I created a Huffman encoder that reads file input, finds the Huffman encoding of its contents, uses the encoder to encode the file, and the decoder to decode the file to its original state. Included in the program files are a variety of functions necessary to read input, create a node ADT, create a Huffman encoder, utilize a priority queue ADT, traverse the Huffman tree using a stack ADT, as well as decode the encoded file using the stack ADT and recursion. Also included in the encoder program are command line options that take in command line input to specify different variables as well as a decoder program that similarly takes in command line input for various options.

##
## Building the Program

Run these commands:

```
make
make clean
make all
make format
make encode
make decode
```

These commands build all executables, clean all executables, formats all source code files, builds encode, and builds decode.
##
## Running the Program

Run this command:

```
./encode
```

Followed by any combination of the following:

```
-i -o -v -h
```

As a summary of the command line options:

-i infile: Specifies the input file to write the compressed input to

-o outfile: Specifies the output file to write the compressed output to

-v: Prints the compression statistics to stderr

-h: Prints out a help message describing the purpose of the program and the command-line options it accepts


Run this command:

```
./decode
```

Followed by any combination of the following:

```
-i -o -v -h
```

As a summary of the command line options:

-i infile: Specifies the input file to decode using Huffman coding

-o outfile: Specifies the output file to write the decompressed input to

-v: Prints the decompression statistics to stderr

-h: Prints out a help message describing the purpose of the program and the command-line options it accepts

##
## Credit

Used the provided C code and pseudocode from the asgn5.pdf from Dr. Long

Used the assignment and program file descriptions from the asgn5.pdf from Dr. Long

Got the code for `read_bytes` and `write_bytes` from TA Eugene's section

Got the code for most of `read_bit` from TA Eugene's section

Used the pseudocode for the while loop in `enqueue()` from TA Eugene's section

Used coding ideas from TA Christian Ocon's section to create struct members in `pq.c`

Used the bitwise shifts and operators code for `code_set_bit`, `code_clr_bit`, and `code_get_bit` from the example provided by Dr. Long in the CSE 13S Code Comments `bv8.h` file

Used the `stack.c` code from my asgn 4 `stack.c`. I used the python pseudocode from Dr. Long in asgn4 to create the functions.

Used TA Eugene's pseudocode for `build_tree` in huffman.c from his section

Based my `build_codes` function off of  Dr. Long's python pseudocode

Based my `dump_tree` function off of Dr. Long's python pseudocode

Copied the error messages and help messages from the resources repo

