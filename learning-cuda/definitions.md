# DEFINITIONS 

## Parallel 

- Multiple pieces of work can be executed concurrently using multiple computational resources.
```txt
Example - 
Worker 1 --> A 
Worker 2 --> B 
Worker 3 --> C
Worker 4 --> D 
```

## Sequential
- Doing tasks one after another in a specific order 
```txt
Example - 
Worker 1 --> A --> B --> C --> D
```

## Computing
- Using a computer to process information by executing instructions and performing operations 
```txt
Example - 
5 + 8 
running a path tracer 
adding two numbers 
```

## Parallel computing 
- Using multiple computational workers or resources to perform multiple pieces of work concurrently, usually by dividing a large problem into smaller independent tasks 
```txt
Example - 
                PROBLEM 
                   | 
    ---------------------------------
    |       |       |       |       |
    A       B       C       D       E   
    |       |       |       |       |
 worker   worker  worker  worker  worker
```
> The pieces of work need to be sufficiently independent for parallel execution to be useful.

## Programming model 
- A way of thinking about how you tell a computer to perform work.
- *Model* - A simplified way of representing something complicated so you can reason about it. 

```txt 
Example - 

Cuda progrmaming model tells us this - 

"Here is a way for you to THINK about when you are giving work to a GPU- 
Threads, Blocks, Grids, Memory, Synchronization"

And we think - 

"1000000 pieces of work?" --> 
"I'll launch a GRID on the GPU" 
"Then I'll divide that GRID into BLOCKS" 
"Then I'll fill those BLOCKS with individual THREADS to execute the work concurrently"
```

## Throughput Capability
  ## Throughput

- The amount of work a system can complete per unit of time.

- High throughput means a system can process a large amount of work over a given period of time.

## API (Application Programming Interface) 
  - A standardized set of rules and code that allows two different software programs to talk to each other, exchange data, and trigger actions inside one another. 
```txt
  GUEST (the client / app) - You sit at the table with an idea of what you want, but you aren't allowed directly into the kitchen to cook for yourself. 

  KITCHEN (the server / database) - Contains all the raw ingredients, tools, and complex logic needed to prepare your request. 

  MENU (the API documentation) - List of allowed requests you can make. You cannot order items that aren't on the menu. 

  WAITER (the API itself) - 
  1) Takes your request 
  2) Translates and delivers it to the KITCHEN 
  3) Brings back your prepared meal
```
  
  - > Graphics API - API specifically designed to let programs interact with graphics systems / GPU functionality. 
   

## Rasterization

- The process of determining which screen/sample locations are covered by projected geometric primitives and generating fragments for those covered locations.

### Simplified mental model

1. 3D Projection
   - 3D geometry is transformed into screen-space coordinates.

2. Coverage Test
   - The rasterizer determines which sample locations are covered by the projected primitive.

3. Fragment Generation
   - Covered locations produce fragments that continue through the graphics pipeline.

4. Fragment Shading
   - A Fragment Shader executes for generated fragment invocations and computes outputs such as colour.    

## Fragment Shader 

- A small program written in a specialized shading language (like GLSL or HLSL) that runs on the GPU. It's sole job in graphics is to calculate the final colour and properties of an individual pixel on the screen. 

  - Keep in mind - Defining a shader alone does not cause it to execute; a graphics draw operation must produce fragments through rasterization, which then triggers fragment-shader invocations.

  > Defining a Fragment Shader does not cause it to execute by itself. A graphics operation must generate fragment invocations for the shader to execute.
  
## VRAM 

- Large, high-bandwith memory pool attached to the GPU, and the GPU uses it to hold data it needs for computation and graphics. 

- VRAM is physically seperate from your normal system RAM on a typical discrete GPU. 

```txt 
         CPU 
          |
      System RAM 
          |
         PCIe 
          |
         GPU 
   ┌───────────────┐
   │   SMs / cores │
   │   L1 cache    │
   │   L2 cache    │
   └───────┬───────┘
           | 
    VRAM (GPU DRAM) 
``` 

 - VRAM isn't the fastest memory available on the GPU. 
 - The GPU has a hierarchy - 
```txt 
FASTEST --- registers 
        --- shared memory 
        --- L1 cache 
        --- L2 cache 
        --- VRAM / global memory 
        --- system RAM 
SLOWEST --- SSD 
``` 

- The fundamemtal idea is that smaller/faster memory is closer to the computation while larger/slower memory is farther away. 

```txt 
Imagine you ahve one thread like this - x = array[i] 
Conceptually the GPU tries to get the data through the memory hierarchy. 

If the data is in the nearby cache 
L1 - hit - insanely quick 
If not 
L1 - miss - L2 - if miss - VRAM 
``` 

- The factory analogy works for this concept 

> GPU performance is heavily influenced by keeping frequently reused data close to the computation. 

