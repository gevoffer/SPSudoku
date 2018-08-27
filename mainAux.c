/*
 * mainAux.c
 *
 *      Authors: Gev Offer
 *      		 Inbar Halevi
 */

#include "mainAux.h"

int local_seed;

void error_malloc(){
	printf("Error: malloc has failed\n");
	exit(0);
}

void error_fgets(){
	printf("Error: fgets has failed\n");
	exit(0);
}

command* create_game_command() {
	command* g_cmd = malloc(sizeof(command));
	if(g_cmd == NULL){
		free(g_cmd);
		error_malloc();
	}
	g_cmd->cmd = INVALID;
	g_cmd->vars[0] = 42; /* 42 was chosen since it's not in use in a 9*9 game, and      */
	g_cmd->vars[1] = 42; /* since it's the answer to life, the universe and everything  */
	g_cmd->vars[2] = 42;
	return g_cmd;
}

void destroy_game_command(command* cmd) {
	free(cmd);
}

gameCell* create_cell() {

	gameCell* cell = malloc(sizeof(gameCell));
	if(cell == NULL){
		free(cell);
		error_malloc();
	}
	cell->value = 0;
	cell->location = -1;
	cell->fixed = false;
	cell->played = false;
	cell->erroneous = false;
	return cell;
}

void destroy_cell(gameCell* cell) {
	free(cell);
}

gameCell* copy_cell(gameCell* cell) {
	gameCell* newCell = create_cell();
	newCell->value = cell->value;
	newCell->fixed = cell->fixed;
	newCell->location = cell->location;
	newCell->played = cell->played;
	newCell->erroneous = cell->erroneous;

	return newCell;
}


gameBoard* create_board() {
	int i;
	gameBoard* board = malloc(sizeof(gameBoard));

	if(board == NULL){
		free(board);
		error_malloc();
	}
	if(board->boardCells == NULL) {
		free(board->boardCells);
		free(board);
		error_malloc();
	}

	for(i = 0; i < (GAME_SIZE * GAME_SIZE); i++) {
		board->boardCells[i] = create_cell();
		board->boardCells[i]->location = i;
	}
	mark_errors = true;
	return board;
}

void destroy_board(gameBoard* board) {
	int i;
	for(i = 0; i < (GAME_SIZE * GAME_SIZE); i++) {
		destroy_cell(board->boardCells[i]);
	}
	free(board);
}

gameBoard* copy_board(gameBoard* board) {
	int i;
	gameBoard* newBoard;
	newBoard = create_board();
	for(i = 0; i < (GAME_SIZE * GAME_SIZE); i++) {
		newBoard->boardCells[i] = copy_cell(board->boardCells[i]);
	}
	return newBoard;
}

void printSepRow() {
	int i;
	for (i=0 ; i < 4*GAME_SIZE+BLOCK_COL_SIZE+1 ; i++ ) {
		printf("-");
	}
	printf("\n");
}

//void printRow(int rowNum, Game* game) {
void printRow(int rowNum, gameBoard* board) {
	int i;
	gameCell* tmpCell;
	for (i = 0 ; i < GAME_SIZE ; i++){
		if (i%BLOCK_COL_SIZE==0) {
			printf("|");
		}
//		tmpCell = game->board->boardCells[rowNum * GAME_SIZE + i];
		tmpCell = board->boardCells[rowNum * GAME_SIZE + i];
		printCell(tmpCell, board);
	}
	printf("|\n");
}

//void printCell(gameCell* cell, Game* game) {
void printCell(gameCell* cell, gameBoard* board) {
	if (cell->value != 0) {printf (" %2d",cell->value);}
	else {printf("   ");}
	if (cell->fixed) {printf(".");}
//	else if ((cell->erroneous) || game->markErrors ){printf("*");}
	else if (board->mark_errors && cell->erroneous){printf("*");}
	else {printf(" ");}
}

//void printBoard(Game* game) {
void print_board(gameBoard* board) {
	int i;
	for (i=0 ; i < GAME_SIZE ; i++) {
		if (i%BLOCK_ROW_SIZE==0) {
			printSepRow();
		}
		printRow(i, board);
	}
	printSepRow();
}

/*
 * return values:
 * 0 - success
 * 1 - cell is fixed
 * 2 - value illegal in given cell
 */
int set_cell(gameBoard* board, gameCell* cell, int value){
	if(cell->fixed){
		return 1;
	}
	if(value > 0 && !check_set_cell(board, cell, value)){
		cell->value = value;
		mark_errors(board, cell);
		return 2;
	}
	cell->value = value;
	return 0;
}

bool check_set_cell(gameBoard* board, gameCell* cell, int value){
	/* checks if value is a possible value of cell */
	int loc;
	loc = cell->location;

	if (cell->value == value) {
		return true;
	}

	bool checkLines = check_lines(board, loc, value);
	bool checkBlock = check_block(board, loc, value);
	return (checkLines && checkBlock);
}

bool check_lines(gameBoard* board, int loc, int value){
	int rowStart;
	int colStart;
	int i;

	rowStart = loc - (loc % GAME_SIZE);
	colStart = loc % GAME_SIZE;

	for(i = 0; i < GAME_SIZE; i++){
		if(board->boardCells[rowStart + i]->value == value) return false;
		if(board->boardCells[colStart + (GAME_SIZE * i)]->value == value) return false;
	}
	return true;
}

bool check_block(gameBoard* board, int loc, int value){
	int blockCol, blockRow, blockHead;
	int i, j;

	blockCol = ((loc % GAME_SIZE) / BLOCK_ROW_SIZE) * BLOCK_COL_SIZE;
	blockRow = ((loc / GAME_SIZE) / BLOCK_COL_SIZE) * BLOCK_ROW_SIZE;
	blockHead = blockRow * GAME_SIZE + blockCol;

	for(i = 0; i < BLOCK_COL_SIZE; i++){
		for(j = 0; j < BLOCK_ROW_SIZE; j++){
			if(board->boardCells[blockHead + (i * GAME_SIZE) + j]->value == value) return false;
		}
	}
	return true;
}

void init_counter_array(int* array) {
	int i;
	for (i = 0 ; i < GAME_SIZE ; i++) {
		array[i] = i+1;
	}
}

void get_possible_values(int* values, int index, gameBoard* board){
	int i;

	init_counter_array(values);
	for(i = 1 ; i <= GAME_SIZE ; i++){
		if (!check_set_cell(board, board->boardCells[index], i)) {
			values[i-1] = 0;
		}
	}
}

int count_possible_values(int* values){
	int pvCounter;
	int i;

	pvCounter = 0;

	for (i = 0 ; i < GAME_SIZE ; i++) {
		if (values[i] != 0) {
			pvCounter ++;
		}
	}
	return pvCounter;
}

int advance_cells(int index, gameBoard* board) {
	while (index < GAME_SIZE * GAME_SIZE) {
		if (board->boardCells[index]->fixed || board->boardCells[index]->played) {
			index += 1;
		}
		else {
			return index;
		}
	}
	return index;
}

/* turns coordinates of cell to number of cell in cells array */
gameCell* get_cell_from_coordinates(gameBoard* board, int x, int y){
	gameCell* cell;
	cell = board->boardCells[(y - 1) * GAME_SIZE + x - 1];
	return cell;
}

void set_seed(int i) {
	local_seed = i;
}

void run_srand() {
	srand(local_seed);
}

void mark_errors(gameBoard* board, gameCell* cell){
	/*TODO: check_set_cells with boolean mark*/
	return;
}

bool no_errors(gameBoard* board){
	int i;
	for(i = 0; i < (GAME_SIZE*GAME_SIZE); i++){
		if(board->boardCells[i]->erroneous){
			return false;
		}
	}
	return true;
}
