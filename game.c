/*
 * game.c
 *
 *      Authors: Gev Offer
 *      		 Inbar Halevi
 */

#include "game.h"

gameBoard* game_board;
gameBoard* solution_board;
int num_of_blanks;

void init_game(){
	bool solved;
	num_of_blanks = GAME_SIZE * GAME_SIZE;
	solved = false;
	solution_board = create_board();
	while (!solved) {
		solved = solver(solution_board, false);
	}
	game_board = copy_board(solution_board);
	set_fixed();
	delete_nonfixed();
}

/* gets from player the amount of fixed cells desired and fixes that many cells */
void set_fixed() {
	int num_fixed_cells, randX, randY;
	/*int local_seed;*/
	gameCell* temp_cell;
	char c;

	num_fixed_cells = -1;
	/*srand(local_seed);*/

	/* ask for a valid input */
	while (num_fixed_cells < 0 || num_fixed_cells > (GAME_SIZE * GAME_SIZE)-1) {
		printf("Please enter the number of cells to fill [0-80]:\n");
		scanf("%d",&num_fixed_cells);
		while ((c = getchar()) != EOF && c != '\n');
		if (num_fixed_cells < 0 || num_fixed_cells > (GAME_SIZE * GAME_SIZE)-1) {
			printf("Error: Invalid number of cells to fill (should be between 0 and 80)\n");
		}
	}

	/* fix desired amount of cells */
	while (num_fixed_cells > 0) {
		randX = (rand() % GAME_SIZE) + 1;
		randY = (rand() % GAME_SIZE) + 1;
		temp_cell = get_cell_from_coordinates(game_board, randX, randY);

		if (temp_cell->fixed == false) {
			temp_cell->fixed = true;
			num_fixed_cells--;
			num_of_blanks--;
		}
	}
}

/* deletes all cell that are not fixed in the board */
void delete_nonfixed() {
	int i;
	for (i = 0; i < GAME_SIZE * GAME_SIZE ; i++) {
		if (game_board-> boardCells[i] -> fixed == false) {
			game_board-> boardCells[i] -> value = 0;
		}
	}
}

void print_game_board(){
	print_board(game_board);
}

void print_solution_board(){
	print_board(solution_board);
}

GAME_COMMAND play_command(command* g_cmd){
	GAME_COMMAND cmdType;
	cmdType = g_cmd->cmd;

	if(cmdType == EXIT){
		printf("Exiting...\n");
		end_game();
	}
	else if (cmdType == RESET) {
		end_game();
	}
	else if(cmdType == SET){
		user_set_cell(g_cmd->vars[0], g_cmd->vars[1], g_cmd->vars[2]);
	}
	else if(cmdType == HINT){
		hint(g_cmd->vars[0], g_cmd->vars[1]);
	}
	else if(cmdType == VALIDATE){
		validate();
	}
	else if(cmdType == PRINT_BOARD){
		print_board(game_board);
	}
	else if(cmdType == INVALID){
		printf("Error: invalid command\n");
	}
	destroy_game_command(g_cmd);
	return cmdType;
}

/* sets value as the value of cell (x,y) */
void user_set_cell(int x, int y, int value){
	int originalValue;
	int set;
	gameCell* cell;

	/*Verify Values*/
	if(x < 1 || x > GAME_SIZE || y < 1 || y > GAME_SIZE || value < 0 || value > GAME_SIZE){
		printf("Error: value not in range 0-%d\n", GAME_SIZE);
		return;
	}

	cell = get_cell_from_coordinates(game_board, x, y);
	originalValue = cell->value;

	set = set_cell(game_board, cell, value);
	if(set == 1){
		printf("Error: cell is fixed\n");
		return;
	}
	else{
		if(value > 0){
			if(originalValue == 0){
				num_of_blanks--;
			}
			cell->played = true;
			print_game_board();
		}
		else if(value == 0){
			if(originalValue > 0){
				num_of_blanks++;
			}
			cell->played = false;
			print_game_board();
		}
		return;
	}
}

/* provides the player with a hint */
void hint(int x, int y){
	int value;
	if(x < 1 || x > GAME_SIZE || y < 1 || y > GAME_SIZE){
		printf("Error: value not in range 1-%d\n", GAME_SIZE);
		return;
	}

	if(!no_errors(game_board)){
		printf("Error: board contains erroneous values\n");
		return;
	}

	if(get_cell_from_coordinates(game_board, x, y)->fixed){
		printf("Error: cell is fixed\n");
		return;
	}

	if(get_cell_from_coordinates(game_board, x, y)->value != 0){
		printf("Error: cell already contains a value\n");
		return;
	}

	bool solvable = ilp_solver(game_board);
	if(solvable){
		value = get_cell_from_coordinates(solution_board, x, y)->value;
		printf("Hint: set cell to %d\n", value);
		return;
	}
	printf("Error: board is unsolvable\n");
}

/* validates that the board is solvable */
void validate() {
	if(!no_errors(game_board)){
		printf("Error: board contains erroneous values\n");
		return;
	}
	gameBoard* temp_board = copy_board(game_board);
	/*TODO: Validate using ILP*/
	bool solvable = ilp_solver(temp_board);
	if (solvable) {
		/*destroy_board(solution_board);
		solution_board = temp_board;*/
		printf("Validation passed: board is solvable\n");
	}
	else {
		printf ("Validation failed: board is unsolvable\n");
	}
	destroy_board(temp_board);
}

bool board_completed() {
	if (num_of_blanks == 0) {
		if(no_errors(game_board)){
			return true;
		}
		printf("Puzzle solution erroneous\n");
	}
	return false;
}

void end_game(){
	destroy_board(game_board);
	destroy_board(solution_board);
}

bool ilp_solver(gameBoard* board){
	/*TODO: ILP Solver*/
	/*Changes solution board if solved, otherwise return false*/
	return true;
}

