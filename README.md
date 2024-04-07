# 2x2-Rubiks-Cube-Optimal-Solver-IDDFS

**Rubik’s Cube Theory**
Combinatorially, there are 3,674,160 valid states that a 2x2 Rubik’s cube can be in and any state can be solved in 11 turns or less (when making 90° or 180°). See the Rubik's Cube Wiki for a more detailed explanation. 

**How it Works**
This solver uses the IDDFS (iterative deepening depth-first search) algorithm to explore the possible states of the 2x2 Rubik’s cube. It begins by performing a depth-first search at a cutoff depth of 1, gradually increasing the cutoff depth until a solution is found. Depth-first search is a method of traversing a tree by exploring as far as possible along one branch, until it is on a leaf node or below the cutoff depth, before backtracking to move onto a different branch. By using depth-first search with gradually increasing cutoff depths, we ensure that the optimal solution (solution with the least amount of moves) will always be found. Further, this approach keeps memory usage relatively low, in comparison to breadth-first search, which is the other common way to traverse graphs. 

**How to Use**
1. Download the files
2. In a terminal shell, navigate to the directory named“2x2-Rubiks-Cube-Optimal-Solver-IDDFS” and type in “./main” to execute the program. 
3. The program will prompt you to enter the number of scrambles, which can be any positive integer. 
4. The program will then prompt you to enter each scramble move separately. To input a scramble move, use standard Rubik’s cube notation. 
5. After all scramble moves are entered, the program will run, returning an optimal solution, the time it took to find the solution, and the solved state of the Rubik’s cube. 

