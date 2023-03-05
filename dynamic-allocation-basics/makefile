pointer_main=./src/pointer.c
pointer_output=./bin/pointer.exe

malloc_main=./src/malloc.c
malloc_output=./bin/malloc.exe

includes=-I./include
libs=-L./bin

compiler=gcc
warn=-Wall -Wextra -Werror -pedantic
flags=-std=c99

default: $(malloc_main) $(pointer_main)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(pointer_main) -o $(pointer_output)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(malloc_main) -o $(malloc_output)

list:
	echo "Usage\n"
	echo "make: compile all examples"
	echo "make malloc: run malloc example"
	echo "make pointer: run pointer example"

malloc: $(malloc_output)
	./$(malloc_output)

pointer: $(pointer_output)
	./$(pointer_output)