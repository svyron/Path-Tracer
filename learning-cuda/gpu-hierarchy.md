## SM - Streaming Multiprocessor 

- **What is it?** - MAJOR processing unit inside the GPU 
- **How many?** - Completely GPU dependent 
- Different generations have different SM designs 
- **What does it contain?** - 

```txt 
SM
├── Warp schedulers
├── CUDA/FP32 execution cores
├── Register file
├── Shared memory
├── L1/data cache
├── Tensor cores, depending on architecture
└── other execution hardware 
``` 
- **Usage** - SM is a physical workshop where your blocks actually execute 
- You don't manually choose the SM, the runtime schedules blocks onto the available SMs. 

## Warp 

- Basic unit of execution in a NVIDIA GPU, consisting of a group of 32 threads packed together 
- When you launch a CUDA kernel, the hardware automatically groups your threads into these 32-thread blocks. The GPU operates on a model called SIMT (Single Instruction, Multiple Threads). This means all 32 threads inside a single warp execute the exact same instruction at the exact same time, just on different pieces of data. 
- Warp Allocation: When you define a block size in CUDA (e.g., dim3 blockSize(128);), the GPU splits that block into warps. \(128 \div 32 = 4\) warps. If your block size isn't a multiple of 32 (like 100 threads), the GPU still allocates 4 full warps (128 slots) but leaves the last 28 slots empty and inactive. Rule of thumb: Always make your block size a multiple of 32 (like 128, 256, or 512).
## Warp Scheduler 

- A hardware component that selects which group of threads, called a warp (typically 32 threads) should execute its next instruction on the clock cycle. 
- **Execution Selection** - On every clock cycle, the scheduler looks for an eligible warp (the one whose instructions are fetched, the one whose hardware units are free, the one whose data dependencies are resolved). 
- **Hiding Latency** - If a warp stalls due to slow memory access or a long math operation, the warp scheduler immediately changes to another warp that is ready. This rapid switching keeps the GPU's arithmentic units busy as well as hides latency. 
- **How many?** - On a modern NVIDIA processor a single SM has 4 warp schedulers 

## Registers 

- Fastest, smallest and most expensive type of memory on a processor. 
- It sits directly inside the execution of a GPU chip. 
- Registers store the immediate data (variables) that a thread is actively working on right now (like the inputs or outputs of a math equation).

- **Register Files** -  The massive pool of ultra-fast physical hardware slots that permanently reserves private register space for every active thread on the SM. Think of a register as a single storage locker, and the register file as the entire locker complex. 

- CPUs have like a few dozen of threads per core but GPUs have tens of thousands per SM. 
- In GPUs every active thread gets its own permanent, private registers for its entire lifespan. 
