/*
 * solver.c
 *
 *      Authors: Gev Offer
 *      		 Inbar Halevi
 */

#include "solver.h"


int randindex;


bool solver (gameBoard* board, bool deterministic) {
	bool solved;
	solved = false;
	if (deterministic) {
		solved = deterministic_solver_rec (0, board);
	}
	else {
		solved = randomized_solver_rec (0, board);
	}
	return solved;
}

bool deterministic_solver_rec(int index, gameBoard* board) {
	bool solved;
	gameCell* temp_cell;
	int i, sc;
	int startVal;

	solved = false;
	/* Returns true if there are no further free cells */
	index = advance_cells(index, board);
	if (index >= GAME_SIZE * GAME_SIZE) {
		return true;
	}

	temp_cell = board->boardCells[index];
	startVal = temp_cell->value;
	/* This loop set's the next untested value to the cell's value and advances the recursion */
	for (i = startVal + 1 ; i <= GAME_SIZE ; i++) {
		sc = set_cell(board,temp_cell,i);
		if (sc == 0) {
			if(index == GAME_SIZE * GAME_SIZE -1){
				return true;
			}
			else{
				solved = deterministic_solver_rec (index + 1, board);
			}
		}
		if (solved) {
			return true;
		}
	}
	temp_cell->value = 0;
	return false;
}

bool randomized_solver_rec(int index, gameBoard* board) {
	bool solved;
	gameCell* temp_cell;
	int all_values[GAME_SIZE];
	int* avPointer;
	int i, pvCounter, cellval, randCounter;

	temp_cell = board->boardCells[index];
	pvCounter = GAME_SIZE;
	avPointer = all_values;

	/* Updating the possible values for the cell and the possible values counter */
	get_possible_values(avPointer, index, board);
	pvCounter = count_possible_values(avPointer);

	/* If there are no possible values for the cell return false */
	if (pvCounter == 0) {
		temp_cell->value = 0;
		return false;
	}
	else {
		while (pvCounter > 0) {
			if (pvCounter != 1) { /* Randomly chooses a value out of the possible values */
				randCounter = (rand() % pvCounter) + 1;
				i = 0;
				while (randCounter > 0) {
					if (avPointer[i] != 0) {
						randCounter-- ;
					}
					i++;
				}
				randindex = i - 1;
				cellval = avPointer[randindex];
				avPointer[randindex] = 0;

			}
			else {
				for (i = 0 ; i < GAME_SIZE ; i++) {
					if (avPointer[i] != 0) {
						cellval = avPointer[i];
						avPointer[i] = 0;
					}
				}
			}
			temp_cell->value = cellval;
			pvCounter --;
			solved = next_rand_call(index,board);
			if (solved) {
				return solved;
			}
		}
	}
	temp_cell->value = 0;
	return false;
}

bool next_rand_call (int index, gameBoard* board) {
	bool solved;
	if (index == (GAME_SIZE * GAME_SIZE) -1) {
			return true;
	}
	else {
		solved = randomized_solver_rec(index + 1, board);
		if (solved) {
			return true;
		}
		else {
			return false;
		}
	}
}
