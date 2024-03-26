/*
Solves a two by two Rubik's cube using IDDFS
Author: Bill Wang
Version: 2024-03-06
*/







#include <array> 
#include <chrono> 
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector> 
using namespace std;

class Face;
class Cube;

// Represents a face of the two by two Rubik's cube
class Face
{
    public:
        // Char that represents the color at the top left corner 
        char topLeft;

        // Char that represents the color at the top right corner 
        char topRight;

        // Char that represents the color at the bottom left corner 
        char bottomLeft;

        // Char that represents the color at the bottom right corner 
        char bottomRight;
    
        // Default constructor with no parameters
        Face() {};

        // Custom constructor with parameters to set up the face object when initializing it
        // Param topLeftColor: the color of the corner in the top left position
        // Param topRightColor: the color of the corner in the top right position
        // Param botLeftColor: the color of the corner in the bottom left position
        // Param botRightColor: the color of the corner in the bottom right position
        Face(char topLeftColor, char topRightColor, char botLeftColor, char botRightColor) 
        {
            topLeft = topLeftColor;
            topRight = topRightColor;
            bottomLeft = botLeftColor;
            bottomRight = botRightColor;
        }

        // Checks if the color on each corner of the face is the same
        // Returns true if the colors are the same, false if colors are different
        bool colorIsMatching()
        {
            if ((topLeft == topRight) && (topLeft == bottomLeft) && (topLeft == bottomRight))
            {
                return true;
            }
            else 
            {
                return false;
            }
        }
};

class Cube 
{
    public:
        // Represents the left face of the cube
        Face leftFace;

        // Represents the top face of the cube
        Face topFace;

        // Represents the front face of the cube
        Face frontFace;

        // Represents the bottom face of the cube
        Face bottomFace;

        // Represents the right face of the cube
        Face rightFace;

        // Represents the back face of the cube
        Face backFace;

        // Represents all the availabe moves that the user can use when scrambling the cube
        string availableMoves[18] = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"};

        // The number of moves that the user can use when scrambling the cube
        int NUMAVAILABLEMOVES = 18;

        // Represents the only moves that the agent needs in order to solve the cube
        // For example, the agent doesn't need both R and L 
        // because these moves do the same thing and just orient the cube in different ways
        string neededMoves[9] = {"R2", "F2", "U2", "R", "R'", "F", "F'", "U", "U'"};

        // The number of moves that the agent can use
        int NUMNEEDEDMOVES = 9;

        // Default constructor with no parameters
        Cube(){};

        // Custom constructor with parameters to set up the cube object when initializing it
        // Param left: represents the left face of the cube
        // Param top: represents the top face of the cube
        // Param front: represents the front face of the cube
        // Param bottom: represents the bottom face of the cube
        // Param right: represents the right face of the cube
        // Param back: represents the back face of the cube
        Cube(Face left, Face top, Face front, Face bottom, Face right, Face back)
        {
            leftFace = left;
            topFace = top;
            frontFace = front;
            bottomFace = bottom;
            rightFace = right;
            backFace = back;
        }

        // Prints the cube's state in a readable format for the user 
        void printCube()
        {

            cout << "          ---------\n";
            cout << "          | " << topFace.topLeft << " | " << topFace.topRight << " |\n";
            cout << "          ---------\n";
            cout << "          | " << topFace.bottomLeft << " | " << topFace.bottomRight << " |\n"; 
            cout << "          ---------\n";

            cout << "--------- --------- --------- ---------\n";
            cout << "| " << leftFace.topLeft << " | " << leftFace.topRight << " | ";
            cout << "| " << frontFace.topLeft << " | " << frontFace.topRight << " | ";
            cout << "| " << rightFace.topLeft << " | " << rightFace.topRight << " | ";
            cout << "| " << backFace.topLeft << " | " << backFace.topRight << " |\n";
            cout << "--------- --------- --------- ---------\n";
            cout << "| " << leftFace.bottomLeft << " | " << leftFace.bottomRight << " | ";
            cout << "| " << frontFace.bottomLeft << " | " << frontFace.bottomRight << " | ";
            cout << "| " << rightFace.bottomLeft << " | " << rightFace.bottomRight << " | ";
            cout << "| " << backFace.bottomLeft << " | " << backFace.bottomRight << " |\n";
            cout << "--------- --------- --------- ---------\n";

            cout << "          ---------\n";
            cout << "          | " << bottomFace.topLeft << " | " << bottomFace.topRight << " |\n";
            cout << "          ---------\n";
            cout << "          | " << bottomFace.bottomLeft << " | " << bottomFace.bottomRight << " |\n"; 
            cout << "          ---------\n";
        }

        // Performs a R move on the cube
        // R means to turn the right face clockwise by 90 degrees
        void R()
        {
            Face oldFrontFace = frontFace;
            Face oldTopFace = topFace;
            Face oldBackFace = backFace;
            Face oldBottomFace = bottomFace;
            Face oldRightFace = rightFace;

            frontFace.topRight = oldBottomFace.topRight;
            frontFace.bottomRight = oldBottomFace.bottomRight;
            topFace.topRight = oldFrontFace.topRight;
            topFace.bottomRight = oldFrontFace.bottomRight;
            backFace.topLeft = oldTopFace.bottomRight;
            backFace.bottomLeft = oldTopFace.topRight;
            bottomFace.bottomRight = oldBackFace.topLeft;
            bottomFace.topRight = oldBackFace.bottomLeft;
            rightFace.topRight = oldRightFace.topLeft;
            rightFace.bottomRight = oldRightFace.topRight;
            rightFace.bottomLeft = oldRightFace.bottomRight;
            rightFace.topLeft = oldRightFace.bottomLeft;
        }

        // Performs a R prime move on the cube
        // R prime means to turn the right face counterclockwise by 90 degrees
        void RPrime()
        {            
            for (int i = 0; i < 3; i++)
            {
                R();
            }
        }

        // Performs a R2 move on the cube
        // R2 means to turn the right face by 180 degrees
        void R2()
        {
            for (int i = 0; i < 2; i++)
            {
                R();
            }
        }

        // Performs a U move on the cube
        // U means to turn the top face clockwise by 90 degrees
        void U()
        {
            Face oldFrontFace = frontFace;
            Face oldTopFace = topFace;
            Face oldBackFace = backFace;
            Face oldRightFace = rightFace;
            Face oldLeftFace = leftFace;

            frontFace.topLeft = oldRightFace.topLeft;
            frontFace.topRight = oldRightFace.topRight;
            leftFace.topLeft = oldFrontFace.topLeft;
            leftFace.topRight = oldFrontFace.topRight;
            backFace.topRight = oldLeftFace.topRight;
            backFace.topLeft = oldLeftFace.topLeft;
            rightFace.topLeft = oldBackFace.topLeft;
            rightFace.topRight = oldBackFace.topRight;
            topFace.topLeft = oldTopFace.bottomLeft;
            topFace.topRight = oldTopFace.topLeft;
            topFace.bottomRight = oldTopFace.topRight;
            topFace.bottomLeft = oldTopFace.bottomRight;
        }

        // Performs a U prime move on the cube
        // U prime means to turn the top face counterclockwise by 90 degrees
        void UPrime()
        {
            for (int i = 0; i < 3; i++)
            {
                U();
            }
        }

        // Performs a U2 move on the cube
        // U2 means to turn the top face by 180 degrees
        void U2()
        {
            for (int i = 0; i < 2; i++)
            {
                U();
            }
        }

        // Performs a L move on the cube
        // L means to turn the left face clockwise by 90 degrees
        void L()
        {
            Face oldFrontFace = frontFace;
            Face oldTopFace = topFace;
            Face oldBackFace = backFace;
            Face oldBottomFace = bottomFace;
            Face oldLeftFace = leftFace;

            frontFace.topLeft = oldTopFace.topLeft;
            frontFace.bottomLeft = oldTopFace.bottomLeft;
            bottomFace.topLeft = oldFrontFace.topLeft;
            bottomFace.bottomLeft = oldFrontFace.bottomLeft;
            backFace.topRight = oldBottomFace.bottomLeft;
            backFace.bottomRight = oldBottomFace.topLeft;
            topFace.topLeft = oldBackFace.bottomRight;
            topFace.bottomLeft = oldBackFace.topRight;
            leftFace.topLeft = oldLeftFace.bottomLeft;
            leftFace.topRight = oldLeftFace.topLeft;
            leftFace.bottomRight = oldLeftFace.topRight;
            leftFace.bottomLeft = oldLeftFace.bottomRight;
        }

        // Performs a L prime move on the cube
        // L prime means to turn the left face counterclockwise by 90 degrees
        void LPrime()
        {
            for (int i = 0; i < 3; i++)
            {
                L();
            }
        }

        // Performs a L2 move on the cube
        // L2 means to turn the left face by 180 degrees
        void L2()
        {
            for (int i = 0; i < 2; i++)
            {
                L();
            }
        }

        // Performs a D move on the cube
        // D means to turn the bottom face clockwise by 90 degrees
        void D()
        {
            Face oldFrontFace = frontFace;
            Face oldBackFace = backFace;
            Face oldBottomFace = bottomFace;
            Face oldLeftFace = leftFace;
            Face oldRightFace = rightFace;

            frontFace.bottomLeft = oldLeftFace.bottomLeft;
            frontFace.bottomRight = oldLeftFace.bottomRight;
            rightFace.bottomLeft = oldFrontFace.bottomLeft;
            rightFace.bottomRight = oldFrontFace.bottomRight;
            backFace.bottomLeft = oldRightFace.bottomLeft;
            backFace.bottomRight = oldRightFace.bottomRight;
            leftFace.bottomLeft = oldBackFace.bottomLeft;
            leftFace.bottomRight = oldBackFace.bottomRight;
            bottomFace.topLeft = oldBottomFace.bottomLeft;
            bottomFace.topRight = oldBottomFace.topLeft;
            bottomFace.bottomRight = oldBottomFace.topRight;
            bottomFace.bottomLeft = oldBottomFace.bottomRight;
        }

        // Performs a D prime move on the cube
        // D prime means to turn the bottom face counterclockwise by 90 degrees
        void DPrime()
        {
            for (int i = 0; i < 3; i++)
            {
                D();
            }
        }

        // Performs a D2 move on the cube
        // D2 means to turn the bottom face by 180 degrees
        void D2()
        {
            for (int i = 0; i < 2; i++)
            {
                D();
            }
        }

        // Performs a F move on the cube
        // F means to turn the front face clockwise by 90 degrees
        void F()
        {
            Face oldFrontFace = frontFace;
            Face oldBottomFace = bottomFace;
            Face oldTopFace = topFace;
            Face oldLeftFace = leftFace;
            Face oldRightFace = rightFace;

            topFace.bottomLeft = oldLeftFace.bottomRight;
            topFace.bottomRight = oldLeftFace.topRight;
            rightFace.topLeft = oldTopFace.bottomLeft;
            rightFace.bottomLeft = oldTopFace.bottomRight;
            bottomFace.topRight = oldRightFace.topLeft;
            bottomFace.topLeft = oldRightFace.bottomLeft;
            leftFace.topRight = oldBottomFace.topLeft;
            leftFace.bottomRight = oldBottomFace.topRight;
            frontFace.topLeft = oldFrontFace.bottomLeft;
            frontFace.topRight = oldFrontFace.topLeft;
            frontFace.bottomRight = oldFrontFace.topRight;
            frontFace.bottomLeft = oldFrontFace.bottomRight;
        }

        // Performs a F prime move on the cube
        // F prime means to turn the front face counterclockwise by 90 degrees
        void FPrime()
        {
            for (int i = 0; i < 3; i++)
            {
                F();
            }
        }

        // Performs a F2 move on the cube
        // F2 means to turn the front face by 180 degrees
        void F2()
        {
            for (int i = 0; i < 2; i++)
            {
                F();
            }
        }

        // Performs a B move on the cube
        // B means to turn the back face clockwise by 90 degrees
        void B()
        {
            Face oldBackFace = backFace;
            Face oldBottomFace = bottomFace;
            Face oldTopFace = topFace;
            Face oldLeftFace = leftFace;
            Face oldRightFace = rightFace;

            topFace.topLeft = oldRightFace.topRight;
            topFace.topRight = oldRightFace.bottomRight;
            leftFace.topLeft = oldTopFace.topRight;
            leftFace.bottomLeft = oldTopFace.topLeft;
            bottomFace.bottomLeft = oldLeftFace.topLeft;
            bottomFace.bottomRight = oldLeftFace.bottomLeft;
            rightFace.topRight = oldBottomFace.bottomRight;
            rightFace.bottomRight = oldBottomFace.bottomLeft;
            backFace.topLeft = oldBackFace.bottomLeft;
            backFace.topRight = oldBackFace.topLeft;
            backFace.bottomRight = oldBackFace.topRight;
            backFace.bottomLeft = oldBackFace.bottomRight;
        }

        // Performs a B prime move on the cube
        // B prime means to turn the back face counterclockwise by 90 degrees
        void BPrime()
        {
            for (int i = 0; i < 3; i++)
            {
                B();
            }
        }

        // Performs a B2 move on the cube
        // B2 means to turn the back face by 180 degrees
        void B2()
        {
            for (int i = 0; i < 2; i++)
            {
                B();
            }
        }

        // Maps a string to the function that performs that move
        // Param moveToMakeInRubiksCubeNotation: represents the move to be made in Rubik's cube notation
        void move(string moveToMakeInRubiksCubeNotation)
        {
            if (moveToMakeInRubiksCubeNotation == "R")
            {
                R();
            }
            if (moveToMakeInRubiksCubeNotation == "R'")
            {
                RPrime();
            }
            if (moveToMakeInRubiksCubeNotation == "R2")
            {
                R2();
            }
            if (moveToMakeInRubiksCubeNotation == "L")
            {
                L();
            }
            if (moveToMakeInRubiksCubeNotation == "L'")
            {
                LPrime();
            }
            if (moveToMakeInRubiksCubeNotation == "L2")
            {
                L2();
            }
            if (moveToMakeInRubiksCubeNotation == "U")
            {
                U();
            }
            if (moveToMakeInRubiksCubeNotation == "U'")
            {
                UPrime();
            }
            if (moveToMakeInRubiksCubeNotation == "U2")
            {
                U2();
            }
            if (moveToMakeInRubiksCubeNotation == "D")
            {
                D();
            }
            if (moveToMakeInRubiksCubeNotation == "D'")
            {
                DPrime();
            }
            if (moveToMakeInRubiksCubeNotation == "D2")
            {
                D2();
            }
            if (moveToMakeInRubiksCubeNotation == "F")
            {
                F();
            }
            if (moveToMakeInRubiksCubeNotation == "F'")
            {
                FPrime();
            }
            if (moveToMakeInRubiksCubeNotation == "F2")
            {
                F2();
            }
            if (moveToMakeInRubiksCubeNotation == "B")
            {
                B();
            }
            if (moveToMakeInRubiksCubeNotation == "B'")
            {
                BPrime();
            }
            if (moveToMakeInRubiksCubeNotation == "B2")
            {
                B2();
            }
        }

        // Prompts the user to input moves to scramble the cube
        // Param numScrambleMoves: the number of moves for the scramble
        void manualScramble(int numScrambleMoves)
        {
            vector<string> completeScramble;
            for (int i = 0; i < numScrambleMoves; i++)
            {
                cout << "Move #" << i + 1 << ": ";
                string moveToMake;
                cin >> moveToMake;
                move(moveToMake);
                completeScramble.push_back(moveToMake);

            }
            cout << "\nScramble: "; 
            for (int i = 0; i < numScrambleMoves; i++)
            {
                cout << completeScramble[i] << " ";
            }
            cout << endl;
        }

        // Checks if the cube is in a solved state
        // Returns true if the colors on each face are matching, false if colors aren't matching
        bool isSolved()
        {
            if ((leftFace.colorIsMatching() == true) 
                && (topFace.colorIsMatching() == true)
                && (frontFace.colorIsMatching() == true)
                && (bottomFace.colorIsMatching() == true) 
                && (rightFace.colorIsMatching() == true)
                && (backFace.colorIsMatching() == true))
            {
                return true;
            }
            else
            {
                return false;    
            }
        }

        // Solves the cube using iterative deepening depth first search
        // Returns a vector of strings representing the solution
        // If no solution was found, returns empty vector
        vector<string> solve()
        {
            // all 2 by 2 states can be solved in 11 moves
            for (int i = 1; i <= 11; i++)
            {
                vector<string> solution = depthFirstSearch(i);
                if (!solution.empty())
                {
                    return solution;
                }
            }
            vector<string> empty;
            return empty;
        }

        // Depth first search algorithm to find solution
        // Param depth: the cutoff depth 
        // Returns a vector of strings that represent the solution
        vector<string> depthFirstSearch(int depth)
        {
            int counter = 0;
            struct SolutionPath
            {
                vector<string> movesMade;
                Cube cubeState;
            };

            SolutionPath rootNode;

            //"this" is a pointer to the object for which the member function is called  
            // "*this" dereferences the pointer and gives the value of the "Cube" 
            rootNode.cubeState = *this;
            vector<string> noMovesMade;
            rootNode.movesMade = noMovesMade;
            stack<SolutionPath> solutionStack;  
            solutionStack.push(rootNode);

            while (!solutionStack.empty())
            {
                SolutionPath current;
                current = solutionStack.top();
                solutionStack.pop();
                counter++; 
                if (current.cubeState.isSolved() == true)
                {
                    cout << "At depth "<< depth << ", searched: " << counter << " nodes" << endl; 
                    return current.movesMade;
                } 

                if (current.movesMade.size() < depth)
                {
                    for (int i = 0; i < NUMNEEDEDMOVES; i++)
                    {
                        SolutionPath neighbor;
                        neighbor = current; 
                        string moveToMake = neededMoves[i];
                        neighbor.cubeState.move(moveToMake);
                        neighbor.movesMade.push_back(moveToMake);
                        solutionStack.push(neighbor);
                    }
                }
            }
            cout << "At depth " << depth << ", searched: " << counter << " nodes" << endl; 
            vector<string> emptySolutionPath;
            return emptySolutionPath;
        }


};

int main()
{
    Face front;
    front.topRight = front.topLeft = front.bottomRight = front.bottomLeft = 'G';
    Face top; 
    top.topRight = top.topLeft = top.bottomRight = top.bottomLeft = 'W';
    Face back; 
    back.topRight = back.topLeft = back.bottomRight = back.bottomLeft = 'B';
    Face bottom; 
    bottom.topRight = bottom.topLeft = bottom.bottomRight = bottom.bottomLeft = 'Y';
    Face left; 
    left.topRight = left.topLeft = left.bottomRight = left.bottomLeft = 'O';
    Face right;
    right.topRight = right.topLeft = right.bottomRight = right.bottomLeft = 'R';

    Cube cube(left, top, front, bottom, right, back);

    cout << "Original Cube: " << endl;
    cube.printCube();
    cout << endl;
    cout << "Number of scramble moves: ";
    int numScrambleMoves;
    cin >> numScrambleMoves;
    cube.manualScramble(numScrambleMoves);

    cout << "Scrambled Cube: " << endl;
    cube.printCube(); 
    cout << endl;

    auto start = chrono::high_resolution_clock::now();

    vector<string> solution = cube.solve();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "\nTook " << duration.count() / 1000000 << " seconds to find the solution" << endl;

    if (solution.size() == 0)
    {
        cout << "No Solution Found" << endl;
    }
    else 
    {
        cout << "Solution: ";
        for (int i = 0; i < solution.size(); i++)
        {
            cout << solution[i] << " ";
            cube.move(solution[i]);
        }
        cout << endl;
        cout << "Solved Cube: " << endl;
        cube.printCube();
    }
}