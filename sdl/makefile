main=src/main.c
includes=-Iinclude
libs=-Lbin -lSDL3 -lm
output=bin/main.exe
compiler=gcc
warn=-Wall -Wextra -Werror -pedantic
flags=-std=c99

default : $(main)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(main) -o $(output)

run: $(output)
	./$(output)
