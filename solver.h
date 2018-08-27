/*
 * solver.h
 *
 *      Authors: Gev Offer
 *      		 Inbar Halevi
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include <stdlib.h>
#include <time.h>
#include "mainAux.h"


/*
 * Gets as input a gameBoard and runs a recursive solver that can be
 * either deterministic or not, according to the boolean input value.
 * Returns true if board was solved, false if not.
 */
bool solver(gameBoard* board, bool deterministic);

/*
 * Gets as input a gameBoard and tries to recursively solve the board in a
 * deterministic way, assuming that all cells up until the cell of the
 * provided index are full. Returns true if board was solved, false if not.
 */
bool deterministic_solver_rec(int index, gameBoard* board);

/*
 * Gets as input a gameBoard and tries to recursively solve the board in a
 * randomized way, assuming that all cells up until the cell of the
 * provided index are full. Returns true if board was solved, false if not.
 */
bool randomized_solver_rec(int index, gameBoard* board);

/*
 * Gets as input an index of a cell and a board, and returns true if index
 * is the last index, or calls randomized_solver_rec for the next cell and
 * returns it's output.
 */
bool next_rand_call (int index, gameBoard* board);

#endif /* SOLVER_H_ */
