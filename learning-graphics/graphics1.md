# PETER SHIRLEY - FUNDAMENTALS OF GRAPHICS 

## 1.3 | 1.4 

### Some needed points

- API - A bunch of functions you call to do an operation 
- Graphics API - Functions for telling the computer what to draw 
- UI API - Fucntions for keyboard/mouse/window interaction 
- Graphics Pipeline - The machinery that turns 3D objects into pixels 
- Z - Buffer - Keeps track of what's in front 
- 4D Homogenous coordinates - A mathematical trick that makes 3D transformations easier 
- LOD (Level of Detail)- Use fewer triangles when objects are far away 
- Framebuffer - Basically it is the image that is currently being built. It it is the storage containing the pixel data for the image that has to be rendered. 

### The Summary  
```mermaid
graph TD
    %% Nodes Definitions
    Prog[GRAPHICS PROGRAM]
    GAPI[GRAPHICS API]
    UI[UI API<br>keyboard/mouse<br>window/events]
    GPU[GPU]
    Pipe[GRAPHICS PIPELINE]
    Model[3D MODEL<br>vertices + △]
    Trans[MODEL TRANSFORM<br>move / rotate / scale]
    World[WORLD]
    Cam[CAMERA / VIEW]
    Proj[PROJECTION<br>3D → 2D]
    Tri[TRIANGLES]
    Rast[RASTERIZE<br>triangles → pixels]
    Shade[SHADING]
    ZBuf[Z-BUFFER<br>depth test]
    FB[FRAMEBUFFER]
    Scr[SCREEN]

    %% Structural Edges
    Prog --> GAPI
    Prog --> UI
    GAPI --> GPU
    GPU --> Pipe
    Pipe --> Model
    Model --> Trans
    Trans --> World
    World --> Cam
    Cam --> Proj
    Proj --> Tri
    Tri --> Rast
    
    %% Split path
    Rast --> Shade
    Rast --> ZBuf
    
    %% Merge path
    Shade --> FB
    ZBuf --> FB
    FB --> Scr

    %% Styling (Optional but makes it look clean)
    style Prog fill:#2c5282,stroke:#4299e1,stroke-width:2px,color:#fff
    style Pipe fill:#2c5282,stroke:#4299e1,stroke-width:2px,color:#fff
    style Scr fill:#2c5282,stroke:#4299e1,stroke-width:2px,color:#fff
``` 

## 1.5 

## The Summary 

- Graphics involves huge amounts of numerical computation 
- Floating-point arithmetic follows IEEE 754 
- There are special values - +∞ | −∞ | NaN 
- For any positive number "a", the rules involving division by INFINITY hold - 
```txt
+a / (+∞) = +0
−a / (+∞) = −0
+a / (−∞) = −0
−a / (−∞) = +0 
``` 

- Some other operations - 
```txt 
∞ + ∞ = +∞
∞ − ∞ = NaN
∞ × ∞ = ∞
∞ / ∞ = NaN
∞ / a = ∞
∞ / 0 = ∞
0 / 0 = NaN 
``` 

- Rules related to NaN - 
1. Any arithmetic expression that includes NaN results in NaN.
2. Any Boolean expression involving NaN is false. 
