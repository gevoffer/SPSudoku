/*
 * Parser.c
 *
 *      Authors: Gev Offer
 *      		 Inbar Halevi
 */

#include "Parser.h"

int parser_game_command(char* str) {
	if (strcmp(str,"set") == 0)
		return SET;
	if (strcmp(str,"hint") == 0)
		return HINT;
	if (strcmp(str,"validate") == 0)
		return VALIDATE;
	if (strcmp(str,"print_board") == 0)
		return PRINT_BOARD;
	if (strcmp(str,"reset") == 0)
		return RESET;
	if (strcmp(str,"exit") == 0)
		return EXIT;
	return INVALID;
}

command* game_parse_line(char* str) {
	const char delim[]  = " \t\r\n";
	char input[MAX_LINE_LENGTH], *token;
	char* var_input;
	command* g_cmd;

	g_cmd = create_game_command(); /* default validArg is false! */

	strcpy(input, str);
	token = strtok(input,delim);
	g_cmd->cmd = parser_game_command(token); /* move to MOVE, for example */


	/* if command is SET */
	if (g_cmd->cmd == SET) {
		int i;
		for(i = 0; i < 3; i++){
			var_input = strtok(NULL, delim);
			if(var_input == NULL) {
				g_cmd->cmd = INVALID;
				return g_cmd;
			}
			g_cmd->vars[i] = atoi(var_input);
		}
		return g_cmd;
	}

	/* if command is HINT */
	else if(g_cmd->cmd == HINT) {
		int i;
		for(i = 0; i < 2; i++){
			var_input = strtok(NULL, delim);
			if(var_input == NULL) {
				g_cmd->cmd = INVALID;
				return g_cmd;
			}
			g_cmd->vars[i] = atoi(var_input);
		}
		return g_cmd;
	}
	return g_cmd;
}

command* extract_game_command() {

	command* cmd;
	char input[MAX_LINE_LENGTH];
	printf("Enter your command:\n"); /*TODO: Check why is it not printed!*/
	fgets(input,MAX_LINE_LENGTH,stdin); /* get input from user */
	if(input == NULL){
		error_fgets();
	}
	cmd = game_parse_line(input); /* checks syntax of command */
	return cmd;
}
