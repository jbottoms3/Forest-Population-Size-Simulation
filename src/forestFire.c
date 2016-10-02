/*
 * forestfire.c
 *
 *  Created on: Sep 7, 2016
 *      Author: James Bottoms
 */

#include <stdio.h>
#include <stdlib.h>
#define GRID_DIMENSION (100)

/*
 * Defining 2-D array to represent the forest
 * Initializing variables for loop
 */
int forest[GRID_DIMENSION][GRID_DIMENSION];
int i;
int j;

/*Function that burns the tree at the coordinates that are input
 * and also recursively calls itself to burn adjacent trees if they are in the array
 */

void burn(int x, int y) {
	forest[x][y] = 0;
	if (x - 1 >= 0) {
		if (forest[x-1][y] == 1) {
			burn(x-1,y);
		}
	}
	if (x + 1 < GRID_DIMENSION) {
		if (forest[x+1][y] == 1) {
			burn(x+1,y);
		}
	}
	if (y - 1 >= 0) {
		if (forest[x][y-1] == 1) {
			burn(x,y-1);
		}
	}
	if (y + 1 < GRID_DIMENSION) {
		if (forest[x][y+1] == 1) {
			burn(x,y+1);
		}
	}
}

/*
 * Function that counts the number of trees (1s) in the forest (array)
 */
int countTrees(void) {
	int numTrees = 0;
	/*
	 * loops through array and adds 1 to current value of numTrees if there is a tree
	 */
	for (i = 0; i < GRID_DIMENSION; i = i + 1) {
		for (j = 0; j < GRID_DIMENSION; j = j + 1) {
			if (forest[i][j] == 1) {
				numTrees = numTrees + 1;
			}
		}
	}
	return numTrees;
}


int main(void) {
	/*
	 * Initializing variables
	 * t: number of time steps
	 * f: fire rate
	 * g: growth rate
	 */

	int sumOfP = 0;
	int time;
	int t;
	float f, g;

	f = .05;
	g = .1;
	t = 1000;

	/*
	 * INITIALIZING EMPTY FOREST
	 */
	for (i = 0; i < GRID_DIMENSION; i = i + 1) {
		for (j = 0; j < GRID_DIMENSION; j = j + 1) {
			forest[i][j] = 0;
		}
	}

	/*
	 * Loops one time step at a time from time = 1 to time = t
	 */
	for (time = 1; time <= t; time = time + 1) {
		/*
		 * GROWTH PHASE
		 * Determines if cell in array is 0, and if so, with probability g, spawns a tree
		 */

		float randNum;
		srand(0);
		for (i = 0; i < GRID_DIMENSION; i = i + 1) {
			for (j = 0; j < GRID_DIMENSION; j = j + 1) {
				if (forest[i][j] == 0) {
					randNum = rand()%100 + 1;
					randNum = randNum / 100;
					if (randNum <= g) {
						forest[i][j] = 1;
					} else {
						forest[i][j] = 0;
					}
				}
			}
		}
		/*
		 * Prints forest size after the growth phase
		 */
		printf("t = %d:\np%d(after growth) = %d, ",time,time,countTrees());

		/*
		 * FIRE PHASE
		 * Determines if tree exists in cell, and if so, calls the burn function on that cell with probability f
		 */
		for (i = 0; i < GRID_DIMENSION; i = i + 1) {
			for (j = 0; j < GRID_DIMENSION; j = j + 1) {
				if (forest[i][j] == 1) {
					randNum = rand()%100 + 1;
					randNum = randNum / 100;
					if (randNum <= f) {
						burn(i,j);
					}
				}
			}
		}

		/*
		 * Prints the forest size after the fire phase
		 */
		printf("p%d(after fire) = %d\n",time,countTrees());
		/*
		 * Adds final P to running total to be used to calculate average
		 */
		sumOfP = sumOfP + countTrees();

	}

	/*
	 * Prints final average forest size (P)
	 */
	printf("P: %f",(float)sumOfP/(float)t);



	return 0;
}
