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
	int playercount = 2;
	scanf("%d", &playercount);
	fprintf(stderr , "Invalid  number  of  players. Using 2 instead .\n");


	// Get an initial seed that is valid
	int SEED = 2021;
	scanf("%d", &SEED);
	fprintf(stderr , "Invalid  random  seed. Using  2021  instead .\n");


	// Generate pseudorandom numbers
	for(int i = 0; i < playercount; i++) {
		srandom(SEED);
	}	


	// Initialize number of points for each player
	int points[playercount];
	for (int j = 0; j < playercount; j++) {
		points[j] = 0;
	}


	// Looping through each player's turn
	// n is the turn incrementer
	int n = 0;
	// k is the points incrementer
	int k = 0;
	// Condition to end game
	while (points[n % playercount] < 100) {
		// Print player's name
		printf("%s", names[n]);


		// Skip turn and increment points variable if pig lands on side
			if (pig[random() % 7] == pig[0] || pig[random() % 7] == pig[1]) {
				n++;
				k++;
				// Print name of next player
				printf("%s", names[n]);
			}
			
	
			// Loop for each player's turn
			while (pig[random() % 7] != pig[0] || pig[random() % 7] != pig[1]) {
				
	
				// Razorback or Trotter
				if (pig[random() % 7] == pig[2] || pig[random() % 7] == pig[3]) {
					points[k] = points[k] + 10;
					printf("%d", points[k]);
				}
	
	
				// Snouter
				else if (pig[random() % 7] == pig[4]) {
					points[k] = points[k] + 15;
					printf("%d", points[k]);
				}
	
	
				// Jowler
				else if (pig[random() % 7] == pig[5] || pig[random() % 7] == pig[6]) {
					points[k] = points[k] + 5;
					printf("%d", points[k]);
		}
		n++;
		k++;
	

	}

	}




}
