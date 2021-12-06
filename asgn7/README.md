# Assignment 7 - The Great Firewall of Santa Cruz

## Description of Program

This assignment consists of various program files that perform different tasks. The first program file is `bf.c` which contains the BloomFilter ADT and implements three different salts and hashing functions to ensure that any oldspeak found is actually oldspeak. The second program file is `hash.c` which implements the hashing functions. The third file is `bv.c` which will be used to get, set, and clear bits in various other files and functions. The fourth file is `ht.c` and implements a hash table to store words that are oldspeak along with their newspeak translations, and map them to specific keys in the table. The fifth program file is `node.c` and will contain the oldspeak that is found as the key, with the newspeak translation acting as the child of the tree. The sixth file is called `bst.c` and will contain recursive functions to properly order the new insertions of oldspeak into the hash table, and take care of any errors that might occur. The seventh file is called `parser.c` and contains the implementation to look through an input stream and find all the occurrences of oldspeak. The eighth and final program file is called `banhammer.c` and contains the command line input handling which takes care of size specifications in certain functions, the printing of statistics, the printing of a help message, and also contains the program implementation to execute all the program files.

# Building the Program

Run this command:
```
./banhammer
```

Followed by any combination of the following:
```
-h -s -t size -f size
```

As a summary of the command line options:

-h:              Display program help and usage.

-s:           Print program statistics.

-t size:      Specify hash table size (default: 2^16).

-f size:      Specify Bloom filter size (default: 2^20).

## Errors in Code

The Bloom filter load statistic is off by around 0.00534% when compared to the resources statistics 

## Credit

Got `bst_find`, `bst_insert`, `bst_height`, `bst_print`, and `max` from Dr. Long's Lecture 18 slides

Followed the inorder traversal example from Lecture 18 page 22 for `bst_print`

Got `bst_create` and `bst_delete` from tutor Eric Hernandez

Got `node_print` from the asgn7 pdf by Dr. Long

Got the idea to do the if/else statement for `n->oldspeak` from tutor Eric Hernandez in `node_create`

Used the bitwise operators and shifts code for `bv_set_bit`, `bv_clr_bit`, and `bv_get_bit` from the example provided by Dr. Long in the CSE 13S Code Comments `bv8.h` file

Also got `bv_create` and `bv_delete` from Dr. Long's `bv8.h` file

Used tutor Eric Hernandez's pseudocode for all of `ht.c`

Got everything in `bf.c` except `bf_create` from tutor Eric Hernandez

Used the `while (word[i])` from https://www.educative.io/edpresso/what-is-the-tolower-function-in-c for the while loop in `banhammer.c`

Got the bulk of the `banhammer.c` code from tutor Eric Hernandez

Used Dr. Long's `banhammer.c` steps/description from the asgn7.pdf

Got the idea to use left shifting from miles on Discord to set the default values for the command line options

Used the parsing module provided in the asgn7.pdf by Dr. Long in `banhammer.c`

Got the regex pattern from tutor Eric Hernandez for `banhammer.c`

