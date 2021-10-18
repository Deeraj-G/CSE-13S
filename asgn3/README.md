# Assignment 3 - Sorting: Putting your affairs in order

This assignment uses 4 separate programs to implement different sorting methods. insert.c uses the insertion sorting algorithm, shell.c uses the shell sort algorithm, heap.c uses the heap sort algorithm with a max heap, and quick.c uses the quicksort algorithm.  

## Building the Program

Run these commands:

```
make
make clean
make all
make format
make sorting
```

These commands search the program file `sorting.c` as well as the other 4 .c files for errors. They also clang format all program files, clean generated files, build all executables, format all source code files, and build the sorting.
												
## Running the Program

Run this command:

```
./sorting
```

Followed by any combination of the following:

```
-a -e -i -s -q -r -n -p -h
```

As a summary of the tests:

-a: Runs all sorting algorithms

-e: Enables Heap Sort

-i: Enables Insertion Sort.

-s: Enables Shell Sort.

-q: Enables Quick Sort.

-r seed: Specify random seed (default: 13371453).

-n length: Specify number of array elements (default: 100).

-p elements: Specify number of elements to print (default: 100).
												
-h: Display program help and usage

## Errors in Program

If I run `./sorting -q -sr`, the quick sort runs rather than display the help message.

## Credit

Used Dr. Long's python pseudocode for all of the sorting algorithms 

Used TA Eugene's `enum`, `calloc`, and general structure for the sorting.c file 

Used Tutor Brian Mak's `atoi(optarg)` suggestion to read inputs for the command line options
