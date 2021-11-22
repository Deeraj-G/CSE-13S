# Assignment 6 - Public Key Cryptography

## Description of Program

This assignment consists of 3 different programs that  accomplish different tasks. The first program file is keygen.c, and is used as the key generator which produces RSA public and private key pairs. The second program file is encrypt.c which will encrypt files using the public key. The last program file is decrypt.c which will decrypt the encrypted files using the corresponding private key. Keygen.c accepts command line input to specify various values in and inputs. The encryptor and decryptor functions similarly take in command line inputs that specify values like the input and output files to encrypt/decrypt and enable verbose printing. There are also 3 other files called randstad.c which is used to initialize a randstad and clear a randstate, numtheory.c which computes the mathematical portion of the code such as `pow_mod`, `is_prime`, and `mod_inverse`, and rsa.c which does the reading and writing to files portion as well as the encryption and decryption of files.

## Building the Program

Run these commands:

```
make
make clean
make all
make format
make encrypt
make decrypt
make keygen
```

These commands build all executables, clean all executables, format all source code files, build encrypt, build decrypt, and build keygen.

## Running the Program

Run this command:

```
./encrypt
```

Followed by any combination of the following:

```
-h -v -i infile -o outfile -n pvfile
```

As a summary of the command line options for encrypt:

-h:              Display program help and usage.

-v:              Display verbose program output.

-i infile:       Input file of data to encrypt (default: stdin).

-o outfile:      Output file for encrypted data (default: stdout). 

-n pvfile:       Private key file (default: rsa.pub).

##

Run this command:

```
./decrypt
```

Followed by any combination of the following:

```
-h -v -i infile -o outfile -n pvfile
```

As a summary of the command line options for decrypt:

-h:              Display program help and usage.

-v:              Display verbose program output.

-i infile:       Input file of data to decrypt (default: stdin).

-o outfile:      Output file for decrypted data (default: stdout).

-n pvfile:       Private key file (default: rsa.priv).

##

Run this command:

```
./keygen
```

Followed by any combination of the following:

```
-h -v -b bits -i confidence -n pbfile -d pvfile -s seed
```

As a summary of the command line options for keygen:

-h:              Display program help and usage.

-v:              Display verbose program output.

-b bits:         Minimum bits needed for public key n (default: 256).

-i confidence:   Miller-Rabin iterations for testing primes (default: 50).

-n pbfile:       Public key file (default: rsa.pub).

-d pvfile:       Private key file (default: rsa.priv).

-s seed:         Random seed for testing.

## Errors in Code

No errors found so far

## Credit

Used the provided pseudocode from the `asgn6.pdf` from Dr. Long

Used Dr. Long's pseudocode for `gcd`, `mod_inverse`, `pow_mod`, and `is_prime`

Used the assignment and program file descriptions from the `asgn6.pdf` from Dr. Long

Got most of `is_prime` from tutor Eric Hernandez's section

Used the pseudocode for `make_prime` from tutor Eric Hernandez's section

Used Dr. Long's explanation of each function to base my code off of for `rsa.c`

Used TA Eric Hernandez's pseudocode for `rsa_make_pub`

Got the idea of using `feof(infile)` from Miles on Discord and tutor Eric Hernandez

Got the parameters of `mpz_export` from tutor Eric Hernandez for `rsa_decrypt_file`

Used pseudocode from tutor Eric Hernandez for `keygen.c` and `decrypt.c`

Used the steps listed by Dr. Long for `keygen.c`, `encrypt.c`, and `decrypt.c`

Copied the error messages and help messages from the resources repo

Based the structure and setup of the command line options off of Dr. Long's `tsp.c` in asgn4
