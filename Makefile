CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = jeopardy.o questions.o players.o
EXEC = jeopardy.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

jeopardy.o: jeopardy.c jeopardy.h questions.h players.h
	$(CC) $(CFLAGS) -c jeopardy.c

questions.o: questions.c questions.h
	$(CC) $(CFLAGS) -c questions.c

players.o: players.c players.h
	$(CC) $(CFLAGS) -c players.c

clean:
	del /F /Q $(EXEC) $(OBJ) 2>nul || exit 0
