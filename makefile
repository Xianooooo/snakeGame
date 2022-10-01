CC = g++
# DEBUGGER = -g -fsanitize=address
FLAG = -std=c++11 $(DEBUGGER) -I .
LIB = -lncurses
SRCS = main.cpp game.cpp snake.cpp 
MAIN = game

all : $(MAIN)

$(MAIN) : $(SRCS)
	$(CC) $(FLAG) $(SRCS) $(LIB) -o $(MAIN)
