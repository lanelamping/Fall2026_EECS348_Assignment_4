/* Program: EECS 348 Assignment 4

Description: Uses recursive backtracking to solve Sudoku puzzles

Inputs: Takes a Sudoku puzzle text file as a command line argument

Output: Displays the puzzle filename, original puzzle,
all possible solutions, and the total number of solutions

Collaborators: None

Other Sources: ChatGPT

Author: Lane Lamping

Creation Date: 10/15/26

Revision Date: 10/15/26

Revisions: I changed main to accept a puzzle filename as a
command line argument instead of looping through five
hardcoded files
*/

// ChatGPT generated
#include <iostream> // Include input/output stream
#include <fstream> // Include file stream
#include <string> // Include string
using namespace std; // Use standard namespace

// ChatGPT generated
// Class to store and solve a Sudoku puzzle
class Sudoku {
private:
	char board[9][9]; // Store the 9x9 Sudoku board
	int solutionCount; // Count the number of solutions found

public:
    // ChatGPT generated
    // Set up an empty Sudoku board
	Sudoku() {
		solutionCount = 0; // Start with zero solutions

		for (int row = 0; row < 9; row++) { // Go through each row
			for (int col = 0; col < 9; col++) { // Go through each columm
				board[row][col] = '_'; // Set each cell to empty
			}
		}
	}

    // ChatGPT generated
	// Read a Sudoku puzzle from a file
	bool loadPuzzle(string filename) {
		ifstream file(filename);

		if (!file.is_open()) { // Check if the file opened
			cout << "Could not open " << filename << endl; // Print an error message
			return false; // Stop if the file could not open
		}

        // Read each character from the puzzle file
		for (int row = 0; row < 9; row++) { // Go through each row
			for (int col = 0; col < 9; col++) { // Go through each column
				if (!(file >> board[row][col])) { // Try to read the next cell
					cout << "Invalid puzzle file." << endl; // Print an error if a cell is missing
					return false; // Stop if the puzzle file is invalid
				}

                // Check that the cell contains a number or underscore
                if (board[row][col] != '_' &&
				        (board[row][col] < '1' ||
				         board[row][col] > '9')) {
					cout << "Invalid character in puzzle." << endl; // Print an error for invalid characters
					return false; // Stop if the charater is invalid
				}
			}
		}

		file.close(); // Close the puzzle file
		return true; // Return true if the puzzle was loaded
	}

    // ChatGPT generated
	// Print the current Sudoku board
	void printBoard() {
		for (int row = 0; row < 9; row++) { // Go through each row
			if (row > 0 && row % 3 == 0) { // Check if a new block of rows starts
				cout << "------+-------+------" << endl; // Print a divider
			}

			for (int col = 0; col < 9; col++) { // Go through each column
				if (col > 0 && col % 3 == 0) { // Check if a new block of columns starts
					cout << "| "; // Print a divider
				}

				cout << board[row][col] << " "; // Print the cell value and a space
			}

			cout << endl; // Move to the next line after printing a row
		}
	}

    // ChatGPT generated
	// Check if a number can be placed in a cell
	bool isValid(int row, int col, char num) {
		// Check if the number already exists in the row
		for (int i = 0; i < 9; i++) { // Go through each column in the row
			if (board[row][i] == num) { // Check if the number matches
				return false; // Return false if the number is found in the row
			}
		}

		// Check if the number already exists in the column
		for (int i = 0; i < 9; i++) { // Go through each row in the column
			if (board[i][col] == num) { // Check if number matches
				return false; // Return false if the number is found in the column
			}
		}

		// Check if the number already exists in the 3x3 block
		int startRow = (row / 3) * 3; // Find the first row of the block
		int startCol = (col / 3) * 3; // Find the first column of the block

		for (int r = startRow; r < startRow + 3; r++) { // Go through the block's rows
			for (int c = startCol; c < startCol + 3; c++) { // Go through the block's columns
				if (board[r][c] == num) { // Check if the number matches
					return false; // Return false if the number is found in the block
				}
			}
		}

		return true; // Return true if the number can be placed in the cell
	}

    // ChatGPT generated
	// Check if the original puzzle has any conflicting numbers
	bool isStartingBoardValid() {
		for (int row = 0; row < 9; row++) { // Go through each row
			for (int col = 0; col < 9; col++) { // Go through each columns
				if (board[row][col] != '_') { // Check if the cell already has a number
					char num = board[row][col]; // Store the number in a temporary variable
					board[row][col] = '_'; // Temporarily empty the cell

					bool valid = isValid(row, col, num); // Check if the number can be placed in the cell
					board[row][col] = num; // Put the original number back

					if (!valid) { // Check if the number caused a conflict
						return false; // Return false if the original puzzle is invalid
					}
				}
			}
		}

		return true; // Return true if the original puzzle is valid
	}

	// Recursively solve the Sudoku puzzle
	void solve() {
		int row = -1; // Store the row of the next empty cell
		int col = -1; // Store the column of the next empty cell

		// Find the next empty cell
		for (int r = 0; r < 9; r++) { // Go through each row
			for (int c = 0; c < 9; c++) { // Go throgh each column
				if (board[r][c] == '_') { // Check if the cell is empty
					row = r; // Save the empty cell's row
					col = c; // Save the empty cell's column
					break; // Stop checking this row
				}
			}

			if (row != -1) { // Check if an empty cell was found
				break; // Stop checking the rows
			}
		}

		// No empty cells means a solution was found
		if (row == -1) {
			solutionCount++; // Increment the solution count

			cout << "\nSolution " << solutionCount << ":" << endl; // Print the solution number
			printBoard(); // Print the solution
			return;
		}

		// Try every possible digit
		for (char num = '1'; num <= '9'; num++) { // Go through each num
			if (isValid(row, col, num)) { // Check if the number can be placed
				board[row][col] = num; // Place the number

				// Recursively solve the remaining puzzle
				solve(); // Call again

				// Backtrack to try another possibility
				board[row][col] = '_'; // Change the cell back to empty
			}
		}
	}

	// ChatGPT generated
	// Display the puzzle and all solutions
	void run(string filename) {
		cout << "\n================================" << endl; // Print a divider
		cout << "Puzzle: " << filename << endl; // Print the puzzle filename
		cout << "================================" << endl; // Print a divider

		if (!loadPuzzle(filename)) { // Try to load the puzzle file
			return; // Stop if the puzzle file cant be loaded
		}

		cout << "\nOriginal Puzzle:\n" << endl; // Print newline, "Original Puzzle:", and newline
		printBoard(); // Print the original puzzle

		solutionCount = 0; // Reset the solution count

		if (isStartingBoardValid()) { // Check if the original puzzle is valid
			solve(); // Call solve()
		}

		if (solutionCount == 0) { // Check if no solutions were found
			cout << "\nNo solution found" << endl; // Print newline and "No solution found" if no solutions were found
		} else {
			cout << "\nTotal solutions: " // Print newline and "Total solutions: "
			     << solutionCount << endl; // Print the total number of solutions found
		}
	}
};

// ChatGPT generated and revised by Lane Lamping (based on previous code provided by ChatGPT for EECS 348 Assignment 3)
// Main funciton to take a filename from the command line and run the sudoku solver
int main(int argc, char* argv[]) {
    if (argc != 2) { // Check that only one argument is given
        cout << "ERROR: Correct Format: ./Assignment4 <puzzle_file>" << endl; // Print how to use the program if the wrong number of arguments is given
        return 1;
    }

    Sudoku sudoku; // Make a sudoku object
    sudoku.run(argv[1]); // Call run() with the filename from the command line

    return 0; // End the program sucessfully
}