/*
 * main.c
 *
 *      Authors: Gev Offer
 *      		 Inbar Halevi
 */

#include "SPBufferset.h"
#include "Parser.h"
#include "game.h"
#include "solver.h"


int seed;


int main(int argc, char* argv[]) {
	/* initialization */
	if (argc == 1) {
		seed = 5;
	}
	else {
		seed = atoi(argv[1]);
	}
	set_seed(seed);
	run_srand();
	SP_BUFF_SET();

	/* game-play */
	while (true) {
		command* game_command;
		GAME_COMMAND cmdType;
		bool completed = false;
		init_game();
		print_game_board();
		while (completed == false) {
			game_command = extract_game_command();
			cmdType = play_command(game_command);
			if (cmdType == RESET) break;
			else if(cmdType == EXIT) {
				exit(0);
			}

			/* End of game */
			if (board_completed()) {
				printf("Puzzle solved successfully\n");
				completed = true;
				do {
					game_command = extract_game_command();
					if(game_command->cmd != EXIT && game_command->cmd != RESET){
						game_command->cmd = INVALID;
					}
					cmdType = play_command(game_command);
					if(cmdType == EXIT){
						exit(0);
					}
				} while(cmdType != RESET);
			}
		}
	}
	end_game();
	return 0;
}
