/*
 * game.h
 *
 *      Authors: Gev Offer
 *      		 Inbar Halevi
 */

#ifndef GAME_H_
#define GAME_H_

#include <stdlib.h>
#include <time.h>
#include "mainAux.h"
#include "Parser.h"
#include "solver.h"

/*
 * Initialize new game:
 * Calls random solver for generating a new board, gets fixed number from user and deletes
 * unfixed cells in the game board.
 */
void init_game();

/*
 * Gets user input for the number of fixed cells, and sets them as fixed.
 */
void set_fixed();

/*
 * After certain cells are fixed, empties all unfixed cells from the game board.
 */
void delete_nonfixed();

/*
 * Prints the full game board by calling print_board on the game board.
 */
void print_game_board();

/*
 * Prints the full game board by calling print_board on the solution board.
 */
void print_solution_board();

/*
 * After retrieving command, calls the appropriate function of the received command.
 */
GAME_COMMAND play_command(command* g_cmd);

/*
 * Command for setting a cell with a specific value according to user input.
 * Calls set_cell, and prints the appropriate output, either error message or the board.
 */
void user_set_cell(int x, int y, int value);

/*
 * Prints the value of the cell in the given coordinates in the solution board.
 */
void hint(int x, int y);

/*
 * Runs the deterministic solver on the current game board. Indicates whether game could be
 * solved or not. If yes, update the solution board.
 */
void validate();

/*
 * Checks whether there are any more blank cells in the game, returns true if no cells
 * are blank.
 */
bool board_completed();

/*
 * Clears the game and solution boards from the memory before ending the game.
 */
void end_game();

bool ilp_solver(gameBoard* board);

#endif /* GAME_H_ */
