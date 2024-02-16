#explanation on this folder's readme.md
source=./src/main.c ./lib/linked_list.c
includes=-Iinclude
output=./bin/main.exe
compiler=gcc
warn=-Wall -Wextra -Werror -pedantic
flags=-std=c99

default : $(source)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(source) -o $(output)

run: $(output)
	./$(output)
