# Basic makefile example
## About this example
This folder contains multiple examples explaining pointers and dynamic allocation<br>
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
│   ├── malloc.exe
│   ├── pointer_arithmetic.exe
│   ├── pointer_types.exe
│   ├── pointer.exe
│   └── sizeof.exe
├── src
│   ├── malloc.c
│   ├── pointer_arithmetic.c
│   ├── pointer_types.c
│   ├── pointer.c
│   └── sizeof.c
```

## Dynamic memory allocation basics
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
  * The pointer is also stored on the stack. It's also a local variable<br>
  * Lets say it's stored at 0x2000<br>
* Pointers usually take 8 bytes<br>
* In this case magic_location has the type int*<br>
  * On the second example, i'll get into why we type pointers<br>
* When we say magic_location points to magic_number<br>
  * By that we mean that the pointer magic_location has the number 0x1000,<br>
    stored between 0x2000 and 0x2007<br>
#### 1.4 Dereferencing a variable
* The special thing about pointers, is that since we defined they have the address of a variable<br>
  * we can assume that, as long as there wasn't a bug on our program,<br>
  * we can read what is stored at the location it's storing<br>
* We can do this by using the * operator<br>
```c
    *magic_location;
```
* While the & operator means "address of", the * operator means "value at"<br>
  * Another way to say this is we are "dereferencing" the pointer<br>
#### 1.5 pointer.c result
* Run ```make pointer``` to run the following example
```c
printf("value of magic_number = %d\n", magic_number);
printf("value of magic_number = value of *p = %d\n", *magic_location);
printf("location of magic_number = &magic_number = magic_location = %p = %p\n", (void*) magic_location, (void*) &magic_number);
```
* The reason for the (void*) cast will be explained on the next example<br>
* If the stack was allocated as explained above. The output would be
```
value of magic_number = 42
value of magic_number = value of *magic_location = 42
location of magic_number = &magic_number = magic_location = 0x1000
```
* But in reality, every time you run it, magic_number is allocated in a different location. <br>
So the 3rd line will be different<br>

### 2. Pointer types
#### 2.1 NULL
```c
 void *magic_location = NULL;
```
* Creates a pointer on the stack, that points to NULL<br>
  * NULL is a special value that's basically used to convey "invalid address"<br>
* NULL is usually equivalent to the address 0x0<br>
  * This is why it's used as "invalid address", since your program usually won't have access to 0x0<br>
* This means you can do both
```c
    void *magic_location = 0x0;
```
* Or
```c
    void *magic_location = 0;
```
* Even though they are equivalent, you should use NULL, for readability<br>
    * Since it has no runtime cost, and nearly zero compile time cost<br>

#### 2.2 Void pointers
Going back to
```c
void *magic_location = NULL;
```
* As we can see magic_location has type void*<br>
  * By void* we mean that the pointer can point to any type of variable<br>
  * We don't necessarily know what type of variable it's pointing when the variable is declared at compile time<br>
* Void pointers have quite a few uses
  * They can be used to point to any type of variable
  So a lot of standard library memory functions use this
  * Much like the %p format specifier we used on the previous example
* We can basically read void* as something like any* or generic* or unknown*
* For this reason, to make void* useful, we usually have to type cast it to the type we want to read
```c
magic_location = (void *)magic_number_location;
printf("value magic_location references = %d\n", (int *)magic_location);
magic_location = (void *)magic_char_location;
printf("value magic_location references = %c\n\n", (char *)magic_location);
```
* Running the example above with ```make pointer_types```, we get
```
value magic_location references = 1066
value magic_location references = *
```
 * The reason we need to type cast a void*, before reading it, has more to do with why we type pointers
    * Because when we read the value a pointer points to, we need to know how many bytes to read
    * Since different types have different sizes. And the pointer only has the address to the first byte
    * The way C manages this, is by having typed pointers
        * So you don't have to say how many bytes to read every time
        * This way, whenever you read a int*, you read the from the first address and the next 4 bytes
        * For char*, first address and the next 1 byte
        * For structs, first address and the next sizeof(struct) bytes
        * And so on for other types
    * Note that the sizeof a pointer is always the same, regardless of the type it's pointing to
        * This is because the pointer only stores the address of the first byte of the variable
        * That is why sizeof(int) != sizeof(char), but sizeof(int*) == sizeof(char*)
  * On the next example i'll explain the sizeof operator
### 3. sizeof
* The sizeof operator is used to get the size of a type
```c
    sizeof(int);
    sizeof(char);
    sizeof(struct my_struct);
```
* The sizeof operator is also used to get the size of a variable's type
```c
    int magic_number = 42;
    sizeof(magic_number);
    char magic_char = 42;
    sizeof(magic_char);
    struct my_struct magic_struct = {magic_number, magic_char};
    sizeof(magic_struct);
```
* This is possible because variable types are known at compile time and don't change
* For this reason, the following is not possible
```c
    void *magic_location = &magic_thing;
    sizeof(*magic_location);
```
* Since the type of *magic_location is unknown at compile time
  * Because void* can point to any type
* Or more directly
```c
    sizeof(void);
```
### 4. Pointer arithmetic
#### 4.1 Go through an array
* We can do arithmetic with pointers
```c
    int magic_number_array[] = {42, 1024};
    int *magic_number_location = magic_number_array;
    // equivalent to
    // int *magic_number_location = &magic_number_array[0];
    magic_number_location++;
```
* magic_number_location now points to &magic_number_array[1]
* This is possible because the pointer stores the address of the first byte of the variable
  * And we know what the next int is, since we know how many bytes an int uses to store it's value
```c
int magic_number_array[] = {42, One_every_8_bytes, 1024};
int *magic_number_location = magic_number_array;
printf("value magic_number_location references 0 = magic_number_array[0] = %d", *magic_number_location);
magic_number_location++;
printf("value magic_number_location references 1 = magic_number_array[1] = %d", *magic_number_location);
magic_number_location++;
printf("value magic_number_location references 2 = magic_number_array[2] = %d", *magic_number_location);
```
* Is equivalent to
```c
int magic_number_array[] = {42, One_every_8_bytes, 1024};
printf("value magic_number_location references 0 = magic_number_array[0] = %d", magic_number_array[0]);
printf("value magic_number_location references 1 = magic_number_array[1] = %d", magic_number_array[1]);
printf("value magic_number_location references 2 = magic_number_array[2] = %d", magic_number_array[2]);
```
#### 4.2 Reading through an int-s bytes
* We can also do arithmetic with pointers that don't have the
* "same type" as the original variable that was created on that address
```c
#define POW_2_26 67108864
#define POW_2_16_TIMES_3 (65536 * 3)
#define POW_2_9 512
#define POW_2_0 1
#define One_every_8_bytes POW_2_26 + POW_2_16_TIMES_3 + POW_2_9 + POW_2_0
int magic_number = One_every_8_bytes;
char *magic_char_location = (char *)(&magic_number);
printf("value magic_char_location references = %d", *magic_char_location);
magic_char_location++;
printf("value magic_char_location references = %d", *magic_char_location);
magic_char_location++;
printf("value magic_char_location references = %d", *magic_char_location);
magic_char_location++;
printf("value magic_char_location references = %d", *magic_char_location);
```
* Prints
```
value magic_char_location references = 1
value magic_char_location references = 2
value magic_char_location references = 3
value magic_char_location references = 4
```
#### 4.3 Undefined behavior
* In pointer arithmetic, the programmer has the responsibility to know how many int-s are stored sequentially
  * So he doesn't violate the memory boundaries of his program
* Using pointer arithmetic carelessly will cause plenty of undefined behavior
  * And it's a common source of bugs
  * The worst kind of bugs, since they are usually hard to debug. And may be silent errors
```c
    int magic_number_array[] = {42, 1024};
    int *magic_number_location = &magic_number_array[1];
```
* Since magic_number_array has size 2 int-s, DO NOT DO THIS
```c
magic_number_location++;
```
* It may work, but it may also cause a segmentation fault.
  * Even if it works, it is not guaranteed to work in the future.
  * Even if it never breaks, it most likely results in reading thrash memory.
* This is what we call undefined behavior
```c
    printf("value magic_number_location references = %d", *magic_number_location);
```
* Since magic_number_location points to an address that is not part of magic_number_array
### 5. Malloc
#### 5.1 What is malloc
* Malloc is a function that allocates memory on the heap
* It takes one argument, the size of the memory to allocate in bytes
* It returns a void pointer to the allocated memory, or NULL if it fails
```c
#include <stdlib.h>
void *magic_location = malloc(42);
```
#### 5.2 About allocated memory
* The allocated memory is not initialized
* It is allocated on the heap, as an array
#### 5.3 Freeing allocated memory
* It is the programmer's responsibility to free the allocated memory
* Or this may lead to memory leaks
```c 
#include <stdlib.h>
void *magic_location = malloc(42);
free(magic_location);
```
* The free function takes a void pointer to the memory to free
* Using it on a pointer that was not allocated with malloc will cause undefined behavior
* Usually a segmentation fault caused by the double free
#### 5.4 Why allocate on the heap
* Allocating memory on the heap, happens on the runtime
* Which allows you to read from user input to determine the size of the memory to allocate
```c
int n;
scanf("%d", &n);
struct Point3D *point_heap_array = malloc(sizeof(struct Point3D) * n);
free(point_heap_array);
```
* This is also equivalent
```c
struct Point3D *may_change_type_heap_array = malloc(sizeof(*may_change_type_heap_array) * n);
free(may_change_type_heap_array);
```
* Another advantage is that the allocated memory is not destroyed when the scope it was allocated in ends
* And unlike the stack, it's size is not as limited
* But unless you have any of the reasons above, it's better to allocate on the stack
* It's faster, and it's easier to debug, since the memory is automatically freed when the scope ends