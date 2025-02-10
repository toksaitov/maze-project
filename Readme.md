Accelerating a Maze Generator
=============================

![Maze](https://i.imgur.com/uc17nQR.png)

The aim of this project is to optimize a C program that generates mazes using the [Randomized Depth-first Search](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search) algorithm (Recursive Backtracker). The current implementation of the program takes a significant amount of time to generate large mazes (16384 by 16384 rooms). Your goal is to reduce the program’s execution time. Use the `perf` profiler to gain insight into the runtime and performance of your program, allowing you to make informed decisions on what to optimize. Apply theoretical knowledge from lectures on modern CPU microarchitectures to determine which aspects of the code to accelerate. Additionally, use knowledge from previous courses to make informed optimizations regarding input and output data handling.

## Tasks

1. Upload or clone the source files to our main course server, `auca.space`. Be prepared to copy your work into a private repository that the instructor will provide later for submission. You must measure performance on `auca.space` and not on your computer.
2. Compile `maze.c` using the command: `clang -O3 -o maze maze.c`.
3. Create a copy of the `maze.c` file and name it `maze_optimized.c`.
4. Open `maze_optimized.c` and modify the code to optimize the program, aiming to improve the `seconds time elapsed` measurement for the command `perf stat ./maze_optimized 16384 16384 maze_optimized.pbm` compared to `perf stat ./maze 16384 16384 maze.pbm`. Compile the optimized code with: `clang -O3 -o maze_optimized maze_optimized.c`.
5. Compare the output files using: `vimdiff maze.pbm maze_optimized.pbm`. The files MUST be identical.

## Rules

* Do NOT profile code anywhere except on our server at `auca.space`.
* Do NOT procrastinate and leave the work until the very last moment. If the server is overloaded close to the deadline, you will not be able to obtain accurate measurements. No extensions will be granted for this reason.
* Use the Clang compiler and NOT the GCC compiler to build your code.
* Do NOT use any additional compiler flags aside from `-O3`.
* Do NOT modify the core maze generation algorithm. It MUST remain a [Randomized Depth-first Search](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search), also known as Recursive Backtracker. You may optimize it but must not replace it with a different algorithm.
* Do NOT modify the core stack data structure of the Recursive Backtracker. It must remain a stack. You may change its underlying implementation, but you must not replace it with a different data structure.
* Do NOT generate more than two `.pbm` files in your home directory. Each file exceeds two gigabytes in size. Remove them after submission.
* Do NOT use assembly tricks, intrinsics, or special library functions to accelerate your code. You may only modify the stack’s underlying implementation, optimize the maze generation, delete unnecessary code, or reorganize it. Using different standard library functions for input and output to enhance performance is allowed.

## Recommendations

1. Find good `perf` counters to analyze. A good starting point could be the following: `-e cycles,instructions,branch-instructions,branch-misses,cache-misses,cache-references`.
2. Look into the IPC (Instructions per Cycle), the percentage of branch mispredictions, and cache misses. These metrics should serve as hints for where to focus most of your optimization efforts in `maze_optimized.c`.
3. Splitting variables (if the IPC is low), eliminating small loops (by unrolling them), removing branching code using predication (if branch misprediction is high), using cache-efficient data structures, and making data access predictable (if the cache miss rate is high) are just some of the code modifications you can pursue based on your collected `perf` metrics.
4. You may also achieve a significant performance boost by optimizing input, output, or allocation logic. Use your knowledge from previous courses to assist you here.
5. Remember, if you make significant changes to your algorithm, input, output, or allocation logic, `perf stat` may no longer be useful, as you could end up comparing apples to oranges.
6. We recommend not using AI systems to optimize your code, but we do NOT prohibit their use. Instead, we suggest using them as tutors to help with the C programming language or to strategize your optimization efforts.

## What to Submit

Get the private repository through an invitation on e-Courses. Copy your work into that directory. Commit and push your changes there to GitHub. Do NOT attempt to upload to the public repository. Do NOT attempt to upload the generated `.pbm` files. Submit the URL of your last commit to Moodle before the deadline.

## Deadline

Check Moodle for information about the deadlines.

## Documentation

    man gcc
    man perf

## Links

### C, GDB

* [Beej's Guide to C Programming](https://beej.us/guide/bgc)
* [GDB Quick Reference](http://users.ece.utexas.edu/~adnan/gdb-refcard.pdf)

### Perf

* [Perf Examples](https://www.brendangregg.com/perf.html)
* [Perf Wiki](https://perf.wiki.kernel.org/index.php/Main_Page)

## Books

* C Programming: A Modern Approach, 2nd Edition by K. N. King
