CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS =
OBJ = jeopardy.o questions.o players.o
TARGET = jeopardy.exe

# Link the program
$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile the source files into object files
jeopardy.o: jeopardy.c jeopardy.h players.h questions.h
	$(CC) $(CFLAGS) -c $<

questions.o: questions.c questions.h
	$(CC) $(CFLAGS) -c $<

players.o: players.c players.h
	$(CC) $(CFLAGS) -c $<

# Clean the build directory
clean:
	cmd /c del /F /Q $(TARGET) $(OBJ)
