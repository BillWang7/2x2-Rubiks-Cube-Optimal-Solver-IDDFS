# 2x2-Rubiks-Cube-Optimal-Solver-IDDFS

## Rubik’s Cube Theory
Combinatorially, there are 3,674,160 valid states that a 2x2 Rubik’s cube can be in and any state can be solved in 11 turns or less (when making 90° or 180°). See the Rubik's Cube Wiki for a more detailed explanation. 

## How it Works
This solver uses the IDDFS (iterative deepening depth-first search) algorithm to explore the possible states of the 2x2 Rubik’s cube. It begins by performing a depth-first search at a cutoff depth of 1, gradually increasing the cutoff depth until a solution is found. Depth-first search is a method of traversing a tree by exploring as far as possible along one branch, until it is on a leaf node or below the cutoff depth, before backtracking to move onto a different branch. By using depth-first search with gradually increasing cutoff depths, we ensure that the optimal solution (solution with the least amount of moves) will always be found. Further, this approach keeps memory usage relatively low, in comparison to breadth-first search, which is the other common way to traverse graphs. 

## How to Use
1. Download the files
2. In a terminal shell, navigate to the directory named“2x2-Rubiks-Cube-Optimal-Solver-IDDFS” and type in “./main” to execute the program. 
3. The program will prompt you to enter the number of scrambles, which can be any positive integer. 
4. The program will then prompt you to enter each scramble move separately. To input a scramble move, use standard Rubik’s cube notation. 
5. After all scramble moves are entered, the program will run, returning an optimal solution, the time it took to find the solution, and the solved state of the Rubik’s cube. 

## Test Cases & Example Runs
The solver can efficiently solve (< 2 seconds) any state of the 2x2 Rubik’s cube given that the most optimal solution is 6 moves or fewer. In cases where the optimal solution is greater than 6 moves, because the number of available states grows exponentially, the solver can become inefficient. For the worst case where the optimal solution is 11 moves, the solver takes around 4 hours to generate the optimal solution. 

Example 1: 6 move optimal solution

<img width="191" alt="Screenshot 2024-04-06 at 10 40 53 PM" src="https://github.com/BillWang7/2x2-Rubiks-Cube-Optimal-Solver-IDDFS/assets/130268410/bb1ea52e-039d-47d8-b8d9-3c6ba1d889e1">

Example 2: 11 move optimal solution (worst case)

<img width="179" alt="Screenshot 2024-04-06 at 10 41 14 PM" src="https://github.com/BillWang7/2x2-Rubiks-Cube-Optimal-Solver-IDDFS/assets/130268410/273e6fba-1763-4c66-9f4d-4dcf1d4a5a52">

## Potential Optimizations
The algorithm could keep track of all the states that it has already searched. However, this is difficult to implement as storing all of the searched states would take a lot of memory, and the process of checking if a state is searched within the unsorted searched states would require a linear search, which is time-consuming when searching millions of nodes. Alternatively, if there is a way to sort the searched states, then linear search would not be required to check if a node is already searched, and the algorithm would be significantly more time efficient. However, sorting the states of the Rubik’s cube is also a difficult task as there isn’t a direct way to quantify a Rubik’s cube state.
