# Basic makefile example
## About this example
This is a basic static library example. <br>
It contains two unrealistically simple libraries, that i link statically to main. <br>
### How to use this example

compile the libraries
    
    make build_libs

compiles the source file
    
    make

runs the executable
    
    make run

### Folder structure
```
makefile
├── bin
│   └── main.exe
├── include
│   ├── libsquare.h
│   └── libcircle.h
├── lib
│   ├── libsquare.o
│   ├── libcircle.o
│   ├── libsquare.c
│   └── libcircle.c
├── src
│   └── main.c
```

### Building the libraries
#### The "build_libs" rule
* This rule uses the -c flag to compile the source code files into static libraries(.o files)
```makefile
build_libs: $(libs_sources)
	$(compiler) $(flags) $(warn) $(includes) -c $(libs_square_source) -o $(libs_square_static)
	$(compiler) $(flags) $(warn) $(includes) -c $(libs_circle_source) -o $(libs_circle_static)
```
* It expands to:
```makefile
gcc -Wall -Wextra -Werror -Iinclude -c lib/libsquare.c -o lib/libsquare.o
gcc -Wall -Wextra -Werror -Iinclude -c lib/libcircle.c -o lib/libcircle.o
```
#### The default rule
* This rule links the static libraries to the main file and creates the output file
```makefile
default : $(main) $(libs_static)
	$(compiler) $(flags) $(warn) $(includes) $(libs) $(libs_static) $(main) -o $(output)
```
* It expands to:
```makefile
gcc -Wall -Wextra -Werror -Iinclude lib/libsquare.o lib/libcircle.o src/main.c -o bin/main.exe
```
#### The "run" rule
* Creates a rule to run the output file. Use "make run" to run this rule
```makefile
run: $(output)
	./$(output)
```
* It expands to:
```makefile
./bin/main.exe
```
## Outside references
* [Linking static libraries](https://blog.devgenius.io/how-to-create-and-use-a-c-static-library-fcf7b20e6302)
* [When to use static or Dynamic libraries](https://stackoverflow.com/questions/140061/when-to-use-dynamic-vs-static-libraries)
* [Static vs Dynamic libraries](https://www.geeksforgeeks.org/static-vs-dynamic-libraries/)