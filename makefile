CC = gcc
OBJS = main.o mainAux.o game.o solver.o Parser.o
EXEC = nim
COMP_FLAG = -ansi -Wall -Wextra \
-Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
main.o: main.c Parser.h solver.h game.h SPBufferset.h
	$(CC) $(COMP_FLAG) -c $*.c
game.o: game.c game.h mainAux.h Parser.h solver.h
	$(CC) $(COMP_FLAG) -c $*.c
solver.o: solver.c solver.h mainAux.h
	$(CC) $(COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h mainAux.h
	$(CC) $(COMP_FLAG) -c $*.c
mainAux.o: mainAux.c mainAux.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
