#include "names.h"

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// This program takes in user input to decide player count and the seed number, then plays the game Pass the Pigs
int main() {
    // Initialize pig die options
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

    // Find the number of players, handle all possible errors
    int64_t playercount = 0;
    fprintf(stdout, "How many players? ");
    scanf("%" SCNd64, &playercount);

    if (playercount < 2 || playercount > 10) {
        fprintf(stderr, "Invalid  number  of  players. Using 2 instead.\n");
        playercount = 2;
    }

    // Get an initial seed that is valid
    int64_t SEED = 2021;
    fprintf(stdout, "Random seed: ");
    scanf("%" SCNd64, &SEED);

    if (SEED < 0 || SEED > UINT_MAX) {
        fprintf(stderr, "Invalid  random  seed. Using  2021  instead.\n");
        SEED = 2021;
    }

    // Generate pseudorandom numbers
    srandom(SEED);

    // Initialize number of points for each player
    int points[playercount];
    for (int i = 0; i < playercount; i++) {
        points[i] = 0;
    }

    // n is the turn incrementer
    // k is the points incrementer
    int n = 0;
    int k = 0;
    int condition = 1;

    // Loop that oversees all turns and points until the game is won
    while (condition == 1) {

        //Reset condition for each turn
        int minor = 1;

        // Condition to end game
        for (int h = 0; h < playercount; h++) {
            if (points[h] >= 100) {
                printf("\n%s wins with %d points!\n", names[h], points[h]);
                condition = 0;
                minor = 0;
            }
        }

        // Print name of current player
        printf("%s rolls the pig...", names[n % playercount]);

        // Loop for each player's turn, takes care of point tracking and ending a turn when the pig lands on its side
        while (minor == 1) {

            // Variable to contain this round's die position
            int position = pig[random() % 7];

            // End current iteration of loop if Pig lands on Side
            if (position == SIDE) {
                printf(" pig lands on side\n");
                minor = 0;
            }

            // Razorback
            else if (position == RAZORBACK) {
                points[k % playercount] += 10;
                printf(" pig lands on back");
                if (points[k % playercount] >= 100) {
                    printf("\n%s wins with %d points!\n", names[n % playercount],
                        points[k % playercount]);
                    condition = 0;
                    minor = 0;
                }
            }

            // Trotter
            else if (position == TROTTER) {
                points[k % playercount] += 10;
                printf(" pig lands upright");
                if (points[k % playercount] >= 100) {
                    printf("\n%s wins with %d points!\n", names[n % playercount],
                        points[k % playercount]);
                    condition = 0;
                    minor = 0;
                }
            }

            // Snouter
            else if (position == SNOUTER) {
                points[k % playercount] += 15;
                printf(" pig lands on snout");
                if (points[k % playercount] >= 100) {
                    printf("\n%s wins with %d points!\n", names[n % playercount],
                        points[k % playercount]);
                    condition = 0;
                    minor = 0;
                }
            }

            // Jowler
            else if (position == JOWLER) {
                points[k % playercount] += 5;
                printf(" pig lands on ear");
                if (points[k % playercount] >= 100) {
                    printf("\n%s wins with %d points!\n", names[n % playercount],
                        points[k % playercount]);
                    condition = 0;
                    minor = 0;
                }
            }
        }
        n++;
        k++;
    }
}
