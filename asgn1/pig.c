#include <stdlib.h>
#include <stdio.h>
#include "names.h"
#include <limits.h>

int main() {
	// Initialize pig die options
	typedef enum { SIDE , RAZORBACK , TROTTER , SNOUTER , JOWLER } Position;
	const Position pig[7] = {
		SIDE,
		SIDE,
		RAZORBACK,
		TROTTER,
		SNOUTER,
		JOWLER,
		JOWLER
	};

	// Find the number of players
	int playercount = 0;
	fprintf(stdout, "How many players? ");
	scanf("%d", &playercount);
	if (playercount < 2 || playercount > 10) {	
		fprintf(stderr , "Invalid  number  of  players. Using 2 instead .\n");
		playercount = 2;
	}
	printf("%d\n", playercount);


	// Get an initial seed that is valid
	fprintf(stdout, "Random seed: ");
	unsigned int SEED = 0;
	scanf("%u", &SEED);
	if (SEED < 0 || SEED > UINT_MAX) {
                fprintf(stderr, "Invalid  random  seed. Using  2021  instead .\n");
		SEED = 2021;
        }
	printf("%u\n", SEED);


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
	
	
	// Loop for all turns
	while (condition == 1) {


		//Reset condition for each turn
		int minor = 1;


		// Condition to end game
		for (int h = 0; h < playercount; h++) {
			if (points[h] >= 100) {
				printf("%s wins with %d points!\n", names[h], points[h]);
				condition = 0;
				minor = 0;
			}
		}


		// Loop for each player's turn
		while (minor == 1) {
			

			// Variable to contain this round's die position
                	int position = pig[random() % 7];


			// Print name of current player
			printf("%s rolls the pig... ", names[n % playercount]);


			// End current iteration of loop if Pig lands on Side	
			if (position == SIDE) {
				printf("pig lands on side \n");
				minor = 0;
			}


			// Razorback
			else if (position == RAZORBACK) {
				points[k] += 10;
				printf("pig lands on back ");
				printf("%d points\n", points[k]);
				if (points[k] >= 100) {
                                        printf("%s wins with %d points", names[n % playercount], points[k]);
					condition = 0;
					minor = 0;
				}
			}


			// Trotter
			else if (position == TROTTER) {
				points[k] += 10;
				printf("pig lands upright ");
				printf("%d points\n", points[k]); 
				if (points[k] >= 100) {
                                        printf("%s wins with %d points", names[n % playercount], points[k]);
					condition = 0;
                                        minor = 0;
				}
			}


			// Snouter
			else if (position == SNOUTER) {
				points[k] += 15;
				printf("pig lands on snout ");
				printf("%d points\n", points[k]);
				if (points[k] >= 100) {
                                        printf("%s wins with %d points", names[n % playercount], points[k]);
					condition = 0;
                                        minor = 0;
				}
			}
			
			
			// Jowler
			else if (position == JOWLER) {
                                points[k] += 5;
                                printf("pig lands on ear ");
                                printf("%d points\n", points[k]);
                                if (points[k] >= 100) {
                                        printf("%s wins with %d points", names[n % playercount], points[k]);
                                        condition = 0;
                                        minor = 0;
                                }
                        }

		}
		n++;
		k++;

	}




}
