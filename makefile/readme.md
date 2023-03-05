# Basic makefile example
## About this example
This is a basic makefile example. <br>
It's a simple main example. <br>
It contains the usual folder structure i tend to use for c programs. <br>
### How to use this example

compile the shared library
    
    make build_lib

compiles the source file
    
    make 

runs the executable
    
    make run

### Folder structure
```
makefile
├── bin
│   ├──libshapes.dll
│   └── main
├── include
│   └── shapes.h
├── lib
│   ├──libshapes.o
│   └── libshapes.c
├── src
│   └── main.c
```

### What's happening in the Makefile
#### Using the makefile
* You must run "make build_lib" to compile the library's source code into a dynamic library
* Then you can run "make" to compile the main.c file
* And finally, you can run "make run" to run the resulting executable
#### Variables
* The first line creates a variable with the path to main's source code
```makefile
main=src/main.c
```
* -Iinclude tells the compiler to search the include directory for headers (.h files), when using #include during compilation
```makefile
includes=-Iinclude
```
* -Llib tells the compiler to search the bin directory for dynamic libraries
```makefile
libs=-Lbin -lm -lshapes
```
* Variable with the output file path
```makefile
output=bin/main.exe
```
* Variable for choosing a compiler
```makefile
compiler=gcc
```
* Variable with warning flags. Shows all warnings and makes them errors
```makefile
warn=-Wall -Wextra -Werror -pedantic
```
* Variable for other compiler flags
```makefile
flags=-std=c99
```
* Creates a rule to compile the main file, using the previous variables.Run "make" without any arguments to use it, since it's the "default" rule
#### The default rule
```makefile
default : $(main)
    $(compiler) $(flags) $(warn) $(includes) $(libs) $(main) -o $(output)
```
* In this case, whenever you run this rule, it expands into the command
```cmd
gcc -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude -Lbin -lm -lshapes src/main.c -o bin/main.exe
```
##### Here, there are some details to note:
* "gcc -std=c99" compiles the file with the c99 standard
* "-Wall -Wextra -Werror -pedantic" enables all warnings and makes them errors
* "-Iinclude" tells the compiler to search the "include" directory for .h files
* "-Lbin -lm -lshapes" tells the linker to:
    * "-Lbin" tells the linker to search the bin directory for dynamic libraries(.dll/.so)
    * "-lm" tells the linker to use the standard c math library
    * "-lshapes" tells the linker to use libshapes.dll/libshapes.so(which we will create later)
* "src/main.c" is the path to the main file
* "-o bin/main.exe" tells the compiler the output file path

#### The "run" rule
* Creates a rule to run the output file. Use "make run" to run this rule
```makefile
run: $(output)
	./$(output)
```

#### Lib variables
* Here i create variables for the library source code file, the static library and the dynamic library
* They don't need to be specifically here, but i added them after the 
#### The variables
* Path to the library source code file
```makefile
lib_source=lib/libshapes.c
```
* Path to the static library
```makefile
lib_static=lib/libshapes.o
```
* Path to the dynamic library
```makefile
lib_dll=bin/libshapes.dll
```
#### The build_lib rule
* this rule compiles the library source code to a static library(.o), and then to dynamic library(.dll/.so)
```makefile
build_lib:
	$(compiler) -c $(lib_source) $(includes) -o $(lib_static)
	$(compiler) -shared -o $(lib_dll) $(lib_static)
```
##### The first command:
```makefile
    $(compiler) -c $(lib_source) $(includes) -o $(lib_static)
```
* Expands into
```cmd
    gcc -c lib/libshapes.c -Iinclude -o lib/libshapes.o
```
* "-c" tells gcc to compile the library source code file into a ".o" file
* And "-o" tells it to output the resulting static library file to "lib/libshapes.o"
##### The second command:
```makefile
    $(compiler) -shared -o $(lib_dll) $(lib_static)
```
* Expands into
```cmd
    gcc -shared -o bin/libshapes.dll lib/libshapes.o
```
* "-shared" tells gcc to compile the static library "lib/libshapes.o" into a dynamic library
* And "-o" tells it to output the result to "bin/libshapes.dll"
## Outside references
* [GNU make manual](https://www.gnu.org/software/make/manual/make.html)
* [Using dlls](http://www.cygwin.com/cygwin-ug-net/dll.html)