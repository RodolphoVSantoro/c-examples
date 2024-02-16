#explanation on this folder's readme.md
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

lib_source=lib/libshapes.c
lib_static=lib/libshapes.o
lib_dll=bin/libshapes.dll
build_lib: $(lib_source)
	$(compiler) -c $(lib_source) $(includes) -o $(lib_static)
	$(compiler) -shared -o $(lib_dll) $(lib_static)