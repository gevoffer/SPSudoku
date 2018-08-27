/*
 * Parser.h
 *
 *      Authors: Gev Offer
 *      		 Inbar Halevi
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mainAux.h"

#define MAX_LINE_LENGTH 256

/*
 * Receives a string, compares it to the appropriate function and returns the enum
 * of the requested function.
 */
int parser_game_command(char* str);

/*
 * Creates a new instance of gameCommand with the parameters specified by the user.
 */
command* game_parse_line(char* str);

/*
 * Retrieves input from user of a game command, calls game_parse_line for creating command.
 */
command* extract_game_command();

#endif /* PARSER_H_ */
