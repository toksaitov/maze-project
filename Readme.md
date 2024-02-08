Accelerating a Maze Generator
=============================

![Maze](https://i.imgur.com/uc17nQR.png)

The aim of this project is to optimize a C program that generates mazes using the [Randomized Depth-first Search](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search) algorithm (Recursive Backtracker). The current implementation of the program takes a significant amount of time to generate large mazes (16384 by 16384 rooms). Your goal is to reduce the execution time of the program by at least 4 seconds on average for five profiling runs by optimizing the code inside the designated TODO blocks. Use the `perf` profiler to get insight into the runtime and performance of your program to make educated guesses on what to improve. Use the theoretical knowledge from lectures about modern CPU microarchitectures to decide what to focus on accelerating the code.

## Tasks

1. Upload/clone the source files to our course server `auca.space` from your private repository that was given to you by the instructor. You have to measure performance on `auca.space` and not on your computer.
2. Compile `maze.c` with `clang -O3 -o maze maze.c`.
3. Create a copy of the `maze.c` file under the name `maze_optimized.c`.
4. Open the file and find blocks of code outlined with the comments `// TODO: optimize` and `// ---`.
5. Change the code to optimize the program to improve `seconds user` measurement for the `perf stat ./maze_optimized 16384 16384 maze_optimized.pbm` command in comparison to `perf stat ./maze 16384 16384 maze.pbm` command by at least four seconds on average for five runs. To compile the code, use the `clang -O3 -o maze_optimized maze_optimized.c` command.
6. Compare the output files with `vimdiff maze.pbm maze_optimized.pbm`. The files must be the same.

## Rules

* Do NOT profile code anywhere but on our server at `auca.space`.
* Do NOT procrastinate and leave the work to the very last moment. If the server is overloaded close to the deadline, you will not be able to get good measurements. We will not give any extensions for that reason.
* Do NOT change anything anywhere in `maze_optimized.c` outside of the `// TODO: optimize` and `// ---` code.
* Use the Clang compiler and NOT the GCC compiler to build your code.
* Do NOT use any additional compiler flags aside from `-O3`.
* Do NOT change the core maze generation algorithms. It MUST stay a [Randomized Depth-first Search](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search) that is also known as Recursive Backtracker. You may optimize it but not change it to a different one.
* Do NOT change the core stack data structure of the Recursive Backtracker. It must be stack. You may change the underlying implementation of the stack, but not replace it with something else.
* Do NOT generate more than two `.pbm` files in your home directory. Remember that each file is more than two gigabytes in size. Remove the files after submission.
* Do NOT use assembly tricks, intrinsics, or any other special library functions to boost the speed of your code. You are only allowed to change the underlying implementation of the stack or the maze and delete or reorganize the code.

## Recommendations

1. Find good `perf` counters to analyze. A good starting point could be the following: '-e cycles,instructions,branch-instructions,branch-misses,cache-misses,cache-references`.
2. Look into the IPC (Instructions per Cycle), percentage of branch mispredictions, and cache misses. If the IPC rounded is far from at least four or the number of branch or cache misses is not close to zero, that metric has to be considered a hint as to where put most of your effort optimizing things in `maze_optimized.c`.
3. Splitting variables (if the IPC is low), eliminating small loops (unrolling them), and removing branching code by using predication (if branch misprediction is high), using cache-efficient data structures, and making data access predictable (if the cache miss rate is high) — these are just some code modifications that you can pursue based on your collected `perf` metrics.

## What to Submit

Commit and push your changes to your private repository that was given to you by the instructor. Do NOT attempt to upload the generated `.pbm` files. Submit the last commit URL to Moodle before the deadline.

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
