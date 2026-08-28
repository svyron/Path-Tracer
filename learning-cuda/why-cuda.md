# WHY was CUDA Created? (INSANELY SIMPLIFIED)

### WHAT IS CUDA? 

- **CUDA (Compute Unified Device Architecture)** 
- It was introduced to enable any computational workload to use the throughput capability of GPUs independent of graphics APIs 

### The PRE-CUDA Era (GPGPU via graphics APIs) 

 Before CUDA (2006), if you wanted to do math on a GPU, you had to trick it by pretending your numbers were screen pixels inside a Graphics API. 
  - **Data Encoding:** Raw numbers/arrays had to be encoded as RGBA pixel values (RGBA = RED GREEN BLUE ALPHA) and stored inside a **2D Image Texture**. 
  - **Logic Translation:** Mathematical operations were written inside graphics **Fragment Shaders** instead of standard C/C++ functions. 
  - **Execution Trigger:** Programmers tricked the GPU into running calculations by drawing a flat 2D rectangle across the screen to process pixel shaders. 
  - **Result Extraction:** Calculated values had to be decoded back into raw numbers by reading pixel colours off the rendered frame. 

### Why So Painful? 

In the early 2000s, CPUs and GPUs were physically seperate chips that communicated over internal expansion bus standards like PCI or AGP 

- CPUs run C++ - They had full access to system RAM, pointers, stack memory etc 
- Early GPUs were primarily designed around graphics workloads.
- Their graphics pipelines contained fixed-function stages as well as increasingly programmable stages.
- They were not exposed to programmers as general-purpose processors in the same way CPUs were.
- This made using GPUs for general-purpose computation awkward. 

- Programmable shader stages provided programmers with a way to execute custom code within the graphics pipeline.
- Fragment Shaders were particularly useful for early GPGPU techniques because they were executed across rasterized fragments

**Why did Devs render 2D rectangles across the screen?** 

GPUs in those days were designed with one master rule - 

> "When a draw call is issued, process every 3D triangle. Project it to 2D screen coordinates, rasterize it into pixels, and run the Fragment Shader for every single pixel covered by that triangle to calculate its colour."

### The (kinda detailed) Process behind the Computations during the Pre-CUDA Era 

> THE PROBLEM - Shader code doesn't run until you "draw" something. 
  - In graphics, writing a Fragment Shader is like defining a function, but it will not even run a single line of code until the GPU draws geometry onto the screen. 
  - If you issue a draw command for a tiny triangle that covers only 10 pixels, the GPU runs your Fragment Shader 10 times. 
  - This means - to run math across a full 1000 x 1000 array of numbers => 1000000 RGBA vectors, you have to force the GPU to rasterize 1000000 pixels => Fragment Shader had to run 1000000 times. 

> The Trick - Building a 2D rectangle from 2 Triangles 
- 3D GPUs don't have a "draw rectangle" command -- they only understand triangles at the hardware level. 
- In order to cover up the entire screen are, developers defined 2 **right-angled triangles** sharing the hypotenuse to make a flat 2D rectangle (Screen Quad) 
```txt 
Vertex 1 (0,1)          Vertex 2 (1,1)
        ┌───────────────────────┐
        │ \                     │
        │   \                   │
        │     \   TRIANGLE 1    │
        │       \               │
        │         \             │
        │   TRIANGLE 2  \       │
        │                 \     │
        │                   \   │
        └───────────────────────┘
  Vertex 3 (0,0)          Vertex 4 (1,0) 
``` 
> Step by Step Execution of How the "Draw Call" Computed Math 
```txt
(an example)
STEP 1 : MEMORY SETUP 
Store 1000000 RGBA math vectors into a 1000 x 1000 image texture in the VRAM. 
                                |
                                | 
STEP 2 : PASS GEOMETRY 
Send 4 vertices forming 2 triangles (a 1000 x 1000 rectangle) to the grpahics pipeline. 
                                |
                                |
STEP 3 : HARDWARE RASTERIZATION 
The Rasterizer calculates that those 2 triangles cover exactly 1000000 pixels on the screen. 
                                |
                                |
STEP 4 : SPAWING PARALLEL SHADER THREADS 
The GPU automatically spawns 1000000 parallel Fragment Shader instances 
- one for every pixel inside the rectangle 
- Thread 0000001 --> Runs shader code on pixel (0 , 0) 
  Thread 0000002 --> Runs shader code on pixel (0 , 1) 
  ...
  Thread 1000000 --> Runs shader code on pixel (1000 , 1000) 
                                |
                                |
STEP 5 : SAVE OUTPUT ARRAY 
Every shader thread writes its calculated RGBA result into an output frame buffer texture in the VRAM. 
```
### BEST EXAMPLE 

```txt
 ┌────────────────────────────────────────────────────────┐
 │ 1. INPUT (CPU -> GPU VRAM)                             │
 │ You load your arrays into a 2D image texture.          │
 │ Pixel (0,0) = (1.0, 2.0, 3.0, 4.0)  <- Dark red/blue   │
 │ Pixel (0,1) = (5.0, 6.0, 7.0, 8.0)  <- Different color │
 └───────────────────────────┬────────────────────────────┘
                             │
                             ▼
 ┌────────────────────────────────────────────────────────┐
 │ 2. EXECUTION (The 2D Rectangle Draw Call)              │
 │ The GPU rasterizes 2 triangles over the image area.    │
 │ - Thread at (0,0) runs math on Pixel (0,0) values.     │
 │ - Thread at (0,1) runs math on Pixel (0,1) values.     │
 └───────────────────────────┬────────────────────────────┘
                             │
                             ▼
 ┌────────────────────────────────────────────────────────┐
 │ 3. OUTPUT IMAGE (VRAM)                                 │
 │ A brand new 2D image is generated where every single   │
 │ pixel has a different calculated RGBA "color".         │
 │ Pixel (0,0) = (11.0, 40.0, -27.0, 2.0)                 │
 │ Pixel (0,1) = (15.0, 30.0,   2.0, 1.0)                 │
 └───────────────────────────┬────────────────────────────┘
                             │
                             ▼
 ┌────────────────────────────────────────────────────────┐
 │ 4. EXTRACTION (GPU -> CPU Memory)                      │
 │ The CPU reads the raw bytes of the output image back.  │
 │ It ignores the "colors" and reads the floats:          │
 │ Result[0] = (11.0, 40.0, -27.0, 2.0)                   │
 │ Result[1] = (15.0, 30.0,   2.0, 1.0)                   │
 └────────────────────────────────────────────────────────┘
```
### QUESTION - "What if I don't have a nice rectangular number of computations?"

- The number of generated work items does not have to exactly equal the number of useful computations. 
- We can generate slightly more work items than necessary and have the extra ones do nothing. Therefore, even a huge prime number of computations is not fundamentally a problem. 
- This matters a lot because - This shows one of the awkward aspects of using a graphics pipeline for general computation. We are forcing our computation into a graphics-oriented structure. 
- CUDA provides a more direct programming model where we specify a grid of threads for the computation rather than expressing the workload as screen geometry.


### But What Did CUDA Do?

- CUDA provided a dedicated programming model and API for general-purpose computation on NVIDIA GPUs.
- This meant programmers no longer had to express general computation through a graphics-oriented API and rendering pipeline. 
- It provides mechanisms for allocating, transferring, and accessing datain differnt GPU memory spaces.

### WHY CUDA? 

> Simplified mental model --> 
```txt
                    BIG PROBLEM 
                        | 
             LOTS of independent work 
                        | 
                 CPU can do it 
                        | 
             TONS of work is expensive 
                        | 
                       GPU 
        (Built for massive parallel throughput) 
                        | 
        (PRE-CUDA)- GPU was mainly exposed through 
                 graphics APIs 
                        | 
     Make GPUs pretend computation is graphics
                        | 
                   CUDA ENTERS 
                        | 
    A way to launch computation directly on the
                       GPU 
```