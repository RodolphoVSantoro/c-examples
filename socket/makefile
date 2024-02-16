#explanation on this folder's readme.md
main=src/main.c
includes=-Iinclude
libs=-Lbin -lm ./bin/sock.dll
output=bin/main.exe
compiler=gcc
warn=-Wall -Wextra -Werror -pedantic
flags=-std=c11

default : $(main)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(main) -o $(output)

run: $(output)
	./$(output)

lib_source=lib/sock.c
lib_static=lib/sock.o
lib_dll=bin/sock.dll
build_lib: $(lib_source)
	$(compiler) -c $(lib_source) $(includes) -o $(lib_static)
	$(compiler) -shared -o $(lib_dll) $(lib_static)