CC = g++
# DEBUGGER = -g -fsanitize=address
FLAG = -lncurses -std=c++11 $(DEBUGGER) -I .
SRCS = main.cpp snake.cpp fruit.cpp
MAIN = game

all : $(MAIN)

$(MAIN) : $(SRCS)
	$(CC) $(FLAG) $(SRCS) -o $(MAIN)
