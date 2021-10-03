# Assignment 1 - Pass the Pigs

This program runs the game Pass the Pigs. The user inputs the number of players as well as an initial seed, and then the game begins. The first player to reach 100 or more points wins, with different die positions equating to different point amounts.

## Building the Program

Run this command:

```
clang  -Wall -Wextra  -Werror  -Wpedantic  -o pig pig.c
```

This command searches the program file `pig.c` for errors, and then compiles it.

## Running the Program

Run this command:

```
./pig
```

This command runs the file `pig.c` after it's been compiled with the clang command. 

## Errors in Program

My program runs into a small error when the user inputs "asdf" in either input. This is caused by the functionality of `scanf` and how it handles differing input types.
