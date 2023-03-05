pointer_main=./src/pointer.c
pointer_output=./bin/pointer.exe

pointer_types_main=./src/pointer_types.c
pointer_types_output=./bin/pointer_types.exe

malloc_main=./src/malloc.c
malloc_output=./bin/malloc.exe

includes=-I./include
libs=-L./bin

compiler=gcc
warn=-Wall -Wextra -Werror -pedantic
flags=-std=c99

default: $(malloc_main) $(pointer_main) $(pointer_types_main)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(pointer_main) -o $(pointer_output)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(malloc_main) -o $(malloc_output)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(pointer_types_main) -o $(pointer_types_output)

list:
	@echo Usage
	@echo make: compile all examples
	@echo make pointer: run pointer example
	@echo make pointer_types: run pointer_types example
	@echo make malloc: run malloc example

malloc: $(malloc_output)
	./$(malloc_output)

pointer: $(pointer_output)
	./$(pointer_output)

pointer_types: $(pointer_types_output)
	./$(pointer_types_output)