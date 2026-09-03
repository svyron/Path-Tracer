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

# DAY 4 - 28-08-2026 

## Learned 

- A bit of CUDA's past 
- ( definitions.md ) 
- ( why-cuda.md ) 

# DAY 5 - 30-08-2026 

## Revised 

- vec3 class 
- vec3 utilities 
- colour utilities 

# DAY 6 - 31-08-2026 

## Learned 

- ```public``` vs ```private``` 
  - Both of them control who is allowed to access the stuff inside the class. 
  - ```public``` - "code outside the class is allowed to use this" 
  - ```private``` - "code outside the class is NOT allowed to directly access this" (But the class's own functions can access it) 
- ```ray() {}``` allows a ```ray``` object to be created with no arguments. 

# DAY 7 - 02-09-2026 

- Viewport is an imaginary rectangular window sitting in front of your camera 
  - It is the surace through which rays are aimed in the world 
  - 16:9 is used cause it's insanely common 
  - The ratio is used to find the image's height 
  - Later using these dimensions, we can calcualte the viewport's width 
- In C++ statements like these - example - ```image_height = image_height < 1 ? 1 : image_height;``` are called ternary functions 

- First, we decide what our final image looks like. We choose an aspect_ratio of 16/9, meaning the image should be 16 units wide for every 9 units of height. Then we choose image_width = 400, and use the aspect ratio to calculate image_height = 225. So our final image is a 400 × 225 grid of pixels.
- Next, we create an imaginary viewport in 3D space — basically a rectangular window that the camera looks through. We choose viewport_height = 2.0 world units, and calculate its width using the same 16:9 ratio, giving about 3.555 world units. So the image is measured in pixels, while the viewport is measured in 3D world units, but they have the same shape. 
- Then viewport_u = vec3(viewport_width, 0, 0) represents the entire horizontal span of the viewport, while viewport_v = vec3(0, -viewport_height, 0) represents the entire vertical span downward. 
- At this point, we know the size of the whole viewport, but we still need to know how far apart individual pixels are in 3D space. Since the viewport's entire width corresponds to 400 pixels, we divide viewport_u by image_width to get pixel_delta_u — the 3D movement needed to go from one pixel to the next horizontally. 
- Similarly, dividing viewport_v by image_height gives pixel_delta_v — the 3D movement needed to go from one pixel to the next vertically. 
- The chain is: image → image dimensions → viewport → viewport's full horizontal/vertical spans → divide those spans into individual pixel-sized steps. 

- viewport_upper_left =
    camera_center - vec3(0,0,focal_length) - viewport_u / 2 - viewport_v / 2; 

- After everything, change the ray_colour function from the dummy black colour version to something like a blue sky as an example. 
