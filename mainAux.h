/*
 * mainAux.h
 *
 *      Authors: Gev Offer
 *      		 Inbar Halevi
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GAME_SIZE (BLOCK_ROW_SIZE*BLOCK_COL_SIZE)
#define BLOCK_ROW_SIZE 2
#define BLOCK_COL_SIZE 3

/*
 * The enum of all the possible user commands
 */
typedef enum{
	SET,
	HINT,
	VALIDATE,
	PRINT_BOARD,
	RESET,
	EXIT,
	INVALID
} GAME_COMMAND;

/*
 * The struct of a cell in a Sudoku board
 */
typedef struct cell{
	int value;
	int location;
	bool fixed;
	bool played;
	bool erroneous;
} gameCell;

/*
 * Ths struct of a Sudoku board
 */
typedef struct board{
	gameCell* boardCells[GAME_SIZE * GAME_SIZE];
	bool mark_errors;
} gameBoard;

/*
 * The struct of a standard user command
 */
typedef struct command{
	GAME_COMMAND cmd;
	int vars[3];
} command;

/*
 * Prints error message and exits if a malloc error occurs.
 */
void error_malloc();

/*
 * Prints error message and exits if an fgets error occurs.
 */
void error_fgets();

/*
 * Creates and returns a pointer to a standard game command with 3 variables initialized
 * to values that are never in use
 */
command* create_game_command();

/*
 * Gets as input a command and frees it
 */
void destroy_game_command(command* cmd);

/*
 * Creates and returns a pointer to an uninitialized cell with cell value = 0 (=> cell
 * is free), location = -1 (=> cell doesn't recognize it's a part of a board yet), fixed =
 * false (=> cell is unfixed) and played = false (=> user has yet to set cell's value).
 */
gameCell* create_cell();

/*
 * Gets as input a cell and frees it
 */
void destroy_cell(gameCell* cell);

/*
 * Gets as input a cell returns a pointer to it
 */
gameCell* copy_cell(gameCell* cell);

/*
 * Creates and returns a pointer to a GAME_SIZE*GAME_SIZE board with uninitialized
 * cells and returns it
 */
gameBoard* create_board();

/*
 * Gets as input a board and frees it's cells and the board itself
 */
void destroy_board(gameBoard* board);

/*
 * Gets as input a cell returns a pointer to it
 */
gameBoard* copy_board(gameBoard* board);

/*TODO:Document!!*/
void printSepRow();
void printRow(int rowNum, gameBoard* board);
void printCell(gameCell* cell, gameBoard* board);
/*
 * Gets as input a game board and prints it
 */
void print_board(gameBoard* board);

/*
 * Gets as input a board, a cell and an int (value), set's the value to be the cell's
 * value. Returns an Indication int: 0 => success, 1 => cell id fixed, 2 => value
 * illegal in given cell.
 */
int set_cell(gameBoard* board, gameCell* cell, int value);

/*
 * Gets as input a board, a cell and a an int (value), and check if this value is
 * a legal value for that cell in this board. return true if value is legal or
 * false if value is illegal.
 */
bool check_set_cell(gameBoard* board, gameCell* cell, int value);

/*
 * Gets as input a board, an int loc (location) and another int (value), and checks
 * if this value is already in use in the row and column to which the cell in loc
 * belong to. returns false if it's already in use and true if it isn't.
 */
bool check_lines(gameBoard* board, int loc, int value);

/*
 * Gets as input a board, an int loc (location) and another int (value), and checks
 * if this value is already in use in the block to which the cell in loc belong to.
 * returns false if it's already in use and true if it isn't.
 */
bool check_block(gameBoard* board, int loc, int value);

/*
 * Gets as input an int array in the length of GAME_SIZE and initiates it's values
 * to be an increasing series of integer from 1 to GAME_SIZE.
 */
void init_counter_array(int array[GAME_SIZE]);

/*
 * Gets as input a pointer to an int array (valuse), an int (index) and a pointer to a
 * board, sets the array using init_counter_array, and changes every value in the array
 * that is not possible for this cell to be 0.
 */
void get_possible_values(int* values, int index, gameBoard* board);

/*
 * gets as input an array of values where a value that is not zero is a
 * possible value, and returns the number of possible values.
 */
int count_possible_values(int* values);

/*
 * gets as input a gameBoard and some index, and returns the index of the
 * first cell after (and including) this cell that isn't fixed or played.
 */
int advance_cells (int index, gameBoard* board);

/*
 * Gets as input a pointer to a board and two ints (X and Y coordinates) and returns a
 * pointer to the cell in the board's cells array corresponding to these coordinates.
 */
gameCell* get_cell_from_coordinates(gameBoard* board, int x, int y);

/*
 * Gets as input an in and assign to to be the value of seed.
 */
void set_seed(int i);

/*
 * Runs srand() for the variable local_seed.
 */
void run_srand();
void mark_errors(gameBoard* board, gameCell* cell);
bool no_errors(gameBoard* board);
#endif /* MAINAUX_H_ */
