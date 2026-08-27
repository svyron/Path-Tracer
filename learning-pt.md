# DAY 1 — 20-08-2026

## Learned

- PPM image format- How `>` redirects program output to a file
- How to create a PPM image from C++
- How to convert a PPM file to PNG for easier viewing
- Bash scripting basics: `>`, `>>`, `|`, `grep`, `ls`, `ls -la`, `&&`, and `||`
- How to compile C++ using `g++`
- What an executable is and how to run it
- Basic Git and GitHub workflow and how pixel data is represented using RGB values
- Using nested loops in C++ to generate pixels
- CMake basics and the difference between configuring and building

# DAY 2 - 24-08-2026 

## Learned 

- Guards: `#ifndef`, `#define` , `#endif` 
- `class` creates a custom type like example `double`, `int` etc 
- Arrays and indexing 
- Constructors 
- Function return types like `double`, `vec3` 
- `const` - prevents modification 
- `this` - address of the current object 
- `*this` - the current object itself 
- `&` - takes a copy and not the original (saves a lot of ram if used right) 
- Operator overloading functions --> return type | operator | input(s)  
// input --> thing being used in the operation with the current object 

# DAY 3 - 26-08-2026 

## Learned 

- Header files contain declarations or interfaces that other files can use 
- cpp files contain the actual implementation and are compiled seperately 
- `#include "file.h"` → makes the header's contents available to that `.cpp` file. 
- Header files are normally not compiled by themselves. 
- Output stream - a path the data travels through when your program wants to send something out 
- MENTAL MODEL --> RETURN TYPE | OPERATOR BEING DEFINED | LEFT INPUT | RIGHT INPUT 
- (operator+= was used to modify vector 1 where vector 2 remains the same but operator+ is used to add to vectors to produce a new result) 

### Member functions and non-member functions 
- Member functions are defined inside the class. This is cause member functions get the current object automatically through `this` 
- Non-member functioins are defined outside the class. They dont have `this` for vec3, so (say for example a+b) both a→u and a→v are passed explicitly. 
