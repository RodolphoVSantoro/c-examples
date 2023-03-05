# Basic makefile example
## About this example
This is a basic makefile example. <br>
It's a simple main example. <br>
It contains the usual folder structure i tend to use for c programs. <br>
### How to use this example

compiles the examples
    
    make 

list examples
    
    make list

run one of the examples listed by the command above
    
    make example_name

### Folder structure
```
makefile
├── bin
│   ├── pointer.exe
│   └── malloc.exe
├── src
│   ├── malloc.c
│   └── pointer.c
```

## Dynamic memory allocation basics:
### 1. Pointers
#### 1.1 The stack
* Understanding pointers is the key dynamic memory allocation<br>
* When you create global or local function variables<br>
memory is allocated on the stack<br>
* [stack vs heap](https://stackoverflow.com/questions/79923/what-and-where-are-the-stack-and-heap)
```c
int magic_number = 42;
```
* Even with one line of code, a lot happens<br>
The one above means you've created a space on the stack for the magic_number<br>
Since it's an int, it's usually 4 bytes<br>
* Let's say the magic_number is stored at address 0x1000<br>
That means no other variable can be "stored" between 0x1000 and 0x1003<br>
Otherwise, you would have two symbols modifying the same value<br>
* We then write the number 5 to 0x1000<br>
#### 1.2 Referencing a variable
```c
    &magic_number;
```
* When talking about memory, the first important operator we learn is "&".<br>
* It means the "address of" magic_number. In this case, as we defined <br>
it equals to 0x1000 in this case<br>
* Another way to read this line of code, is we are "referencing" magic_number<br>
Since by knowing the address of magic_number, we can read it's value<br>
#### 1.3 Pointing to a variable
```c
int *magic_location = &magic_number;
```
* We then create the pointer magic_location to the address of magic_number<br>
The pointer is also stored on the stack. It's also a local variable<br>
Lets say it's stored at 0x2000<br>
* Pointers usually take 8 bytes<br>
* In this case magic_location has the type int*<br>
On the second example, i'll get into why we type pointers<br>
* When we say magic_location points to magic_number<br>
By that we mean that the pointer magic_location has the number 0x1000,<br>
stored between 0x2000 and 0x2007<br>
#### 1.4 Dereferencing a variable
```c
*magic_location
    printf("value of magic_number = %d\n", magic_number);
    printf("value of magic_number = value of *magic_location = %d\n", *magic_location);
    printf("location of magic_number = &magic_number = magic_location = %p = %p\n", (void*) magic_location, (void*) &magic_number);
```
* The special thing about pointers, is that since we defined they have the address of a variable<br>
we can assume that, as long as there wasn't a bug on our program,<br>
we can read what is stored at the location it's storing<br>
* We can do this by using the * operator<br>
While the & operator means "address of", the * operator means "value at"<br>
Another way to say this is we are "dereferencing" the pointer<br>
#### 1.5 pointer.c result
* Run ```make pointer``` to run the following example
```c
    printf("value of magic_number = %d\n", magic_number);
    printf("value of magic_number = value of *p = %d\n", *magic_location);
    printf("location of magic_number = &magic_number = magic_location = %p = %p\n", (void*) magic_location, (void*) &magic_number);
```
* The reason for the (void*) cast will be explained on the next example<br>
* If the stack was allocated as explained above. The output would be:
```
value of magic_number = 42
value of magic_number = value of *magic_location = 42
location of magic_number = &magic_number = magic_location = 0x1000
```
* But in reality, every time you run it, magic_number is allocated<br>
in a different location. So the 3rd line will be different<br>

### 2. Pointer types