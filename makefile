CC = g++
# DEBUGGER = -g -fsanitize=address
FLAG = -lncurses -std=c++11 $(DEBUGGER) -I .
SRCS = main.cpp game.cpp snake.cpp 
MAIN = game

all : $(MAIN)

$(MAIN) : $(SRCS)
	$(CC) $(FLAG) $(SRCS) -o $(MAIN)
