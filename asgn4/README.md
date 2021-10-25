# Assignment 4 - Perambulations of Denver Long

## Description of Program

This assignment uses 3 separate programs to calculate the shortest path from point A to point B. The first program, graph.c contains a variety of functions that deal with graph creation, deletion, specification of directed vs undirected vertices, and mapping of edges. The second program, stack.c contains functions that are quite similar to those found in graph.c, but deal with a stack. The file contains functions for stack creation, deletion, checking for full or emptiness, checking the size of the stack, returning the last element, pushing more elements into a stack, and printing the contents of the stack. The last program file, path.c, contains functions that create and delete a path, adding vertices to the path, removing a vertex from the path, finding the length and number of vertices of the path, and printing the entirety of the path. The tsp.c file deals with the usage of the various functions to read command line inputs and calculate the shortest Hamiltonian path using depth first search. 

## Building the Program

Run these commands:

```
make
make clean
make all
make format
make tsp
```

These commands search the program file `tsp.c` as well as the other 3 .c files for errors. They also clang format all program files, clean generated files, build all executables, format all source code files, and build the tsp.

## Running the Program

Run this command:

```
./tsp
```

Followed by any combination of the following:

```
-h -v -u -i -o
```

As a summary of the command line options:

-h: Prints the program usage and help.

-v: Enables verbose printing.

-i: Specifies the input file containing the graph (default: stdin)

-o: Specifies the output file of the computed path (default: stdout)

-u: Specifies that the graph is undirected

## Credit

Used C code from Dr. Long in the asgn4.pdf

Based my code off of the function descriptions in the asgn4.pdf by Dr. Long

Implemented TA Christian Ocon's examples to structure my main()

Copied the error messages and help messages from the resources repo

Used TA Omar's code for input scanning
