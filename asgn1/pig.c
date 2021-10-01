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
	fprintf(stdout, "Enter the number of players: ");
	scanf("%d", &playercount);
	if (playercount < 2 || playercount > 10) {	
		fprintf(stderr , "Invalid  number  of  players. Using 2 instead .\n");
		playercount = 2;
	}
	printf("%d\n", playercount);


	// Get an initial seed that is valid
	fprintf(stdout, "Enter an initial seed number: ");
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
	for (int j = 0; j < playercount; j++) {
		points[j] = 0;
	}


	// n is the turn incrementer
	// k is the points incrementer
	int n = 0;
	int k = 0;
	int condition = 1;
	// Loop for all turns
	while (condition == 1) {


		// Condition for each turn
		int minor = 1;


		// Condition to end game
		for (int h = 0; h < playercount; h++) {
			if (points[h] >= 100) {
				printf("%s won the game!", names[h]);
				condition = 0;
			}
		}


		// Variable to contain this round's die position
		const Position position = pig[random() % 7];


		// Print player's name
		printf("It is %s turn\n", names[n % playercount]);
			
	
		// Loop for each player's turn
		while (minor == 1) {
		

			// End current iteration of loop if Pig lands on Side	
                	if (position == pig[0] || position == pig[1]) {
				printf("%s rolled the Side", names[n % playercount]);
				minor = 0;
                	}


			// Razorback or Trotter
			if (position == pig[2] || position == pig[3]) {
				points[k] = points[k] + 10;
				printf("%s rolled a Razorback or Trotter", names[n % playercount]);
				printf("%d\n", points[k]);
			}
	
	
			// Snouter
			else if (position == pig[4]) {
				points[k] = points[k] + 15;
				printf("%s rolled a Snouter", names[n % playercount]);
				printf("%d\n", points[k]);
			}
	
	
			// Jowler
			else if (position == pig[5] || position == pig[6]) {
				points[k] = points[k] + 5;
				printf("%d\n", points[k]);
				printf("%s rolled a Jowler", names[n % playercount]);
			}
			n++;
			k++;
	

		}

	}




}
