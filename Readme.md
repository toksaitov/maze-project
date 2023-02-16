Accelerating a Maze Generator
=============================

![Maze](https://i.imgur.com/uc17nQR.png)

The aim of this project is to optimize a C program that generates mazes using the [Randomized Depth-first Search](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search) algorithm (Recursive Backtracker). The current implementation of the program takes a significant amount of time to generate large mazes (16384 by 16384 rooms). Your goal is to reduce the execution time of the program by at least 5 seconds on average for five profiling runs by optimizing the code inside the designated TODO blocks. Use the `perf` profiler to get insight into the runtime and performance of your program to make educated guesses on what to improve. Use the theoretical knowledge from lectures about modern CPU microarchitectures to decide what to focus on accelerating the code.

## Tasks

1. Upload/clone the `maze.c` source file to our course server `auca.space` from this repository. You have to measure performance on `auca.space` and not on your computer.
2. Compile `maze.c` with `clang -O3 -o maze maze.c`.
3. Create a copy of the `maze.c` file under the name `maze_optimized.c`.
4. Open the file and find blocks of code outlined with the comments `// TODO: optimize` and `// ---`.
5. Change the code to optimize the program to improve `task-clock` measurement for the `perf stat ./maze_optimized 16384 16384 maze_optimized.pbm` command in comparison to `perf stat ./maze 16384 16384 maze.pbm` command by at least five seconds on average for five runs. To compile the code, use the `clang -O3 -o maze_optimized maze_optimized.c` command.
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

## What to Submit

1. In your private course repository that was given to you by the instructor during the lecture, create the path `project-1/`.
2. Put the `maze_optimized.c` file into that directory.
3. Commit and push your repository through Git. Submit the last commit URL to Canvas before the deadline.

## Deadline

Check Canvas for information about the deadlines.

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
