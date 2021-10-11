# Assignment 2 - A Little Slice of π
  
This assignment implements various mathematical functions to compute the square root of a number, as well as the fundamental constants e and π. There are 6 files that contain various mathematical implements. e.c approximates e, newton.c finds the square root of an argument, and the other four files: viete.c, madhava.c, bbp.c, and euler.c approximate π.

## Building the Program

Run these commands:

```
make
make clean
make all
make format
```

These commands search the program file `mathlib-test.c` as well as the other 6 .c files for errors, builds all executables, cleans the generated files, and formats all source code files.

## Running the Program

Run this command:

```
./mathlib-test
```

Followed by:

```
-a -e -b -m -r -v -n -s -h
```

As a summary of the tests:

-a: Runs all tests

-e: Runs e approximation test

-b: Runs Bailey-Borwein-Plouffe π approximation test

-m: Runs Madhava π approximation test

-r: Runs Euler sequence π approximation test

-v: Runs Viète π approximation test

-n: Runs Newton-Raphson square root approximation tests

-s: Enable printing of statistics to see computed terms and factors for each tested function

-h: Display a help message detailing program usage.

This command parses through mathlib-test.c and prints a variety of tests depending on the argument specified.

## Errors in Program

None found so far
