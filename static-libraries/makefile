main=./src/main.c
libs_static_folder=./lib
libs_sources=./lib/libsquare.c ./lib/libcircle.c
libs_static=./lib/libsquare.o ./lib/libcircle.o
output=./bin/main.exe

libs_square_source=./lib/libsquare.c
libs_circle_source=./lib/libcircle.c
libs_square_static=./lib/libsquare.o
libs_circle_static=./lib/libcircle.o

includes=-I./include
libs=-lm
compiler=gcc
warn=-Wall -Wextra -Werror -pedantic
flags=-std=c99

default : $(main) $(libs_static)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(libs_static) $(main) -o $(output)

build_libs: $(libs_sources)
	$(compiler) $(flags) $(warn) $(includes) -c $(libs_square_source) -o $(libs_square_static)
	$(compiler) $(flags) $(warn) $(includes) -c $(libs_circle_source) -o $(libs_circle_static)

run: $(output)
	./$(output)