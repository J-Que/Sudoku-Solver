//Sudoku is a puzzle game where the goal is to fill in a 9 by 9 grid of cells with values of 1-9 where each of the 9 units, rows, and columns can only have one of each digit 1-9.:
//The 9 rows are the vertical subdivsions of the grid containg 9 cells, and in the program, the row number is referenced by the first index of the grid array.
//Likewise the columns are the 9 horizontal subdivisions containing 9 cells, and the column number is referenced by the second index of the grid array.
//Units are the 3 by 3 subdivisions of the grid. There are 9 of them starting off with the uppermost left corner.

//This solver uses the most well known solving algorithm for sudoku known as the backtracking algorithm.
//The steps are:
//1. Find the first empty cell.
//2. If possible, assign the lowest value to the cell without violating any rules.
//3. If no value may be assigned to the cell without conflicts then return to the previously assigned cell, and increase its value to the next possible value
//4. If there is no previously assigned cell then there is no solution to the puzzle.
//5. Continue to the next empty cell and repeat steps 2-5, unitl the puzzle is either solved or is determined to have no solution.

#include <iomanip>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Function that converts char to intger if it is a digit, used for input validation.
int convert(char input) {
	if(isdigit(input)) {
		return (input - 48);
	} else {
		return 0;
	}
}

// A class for sudkoku boards is used as their are several functions used which share some variables and methods.
class sudoku {	
	private:

		// This grid will be used through the class and its methods.
		int grid[9][9];

	public:

		//First, the board is constructed by prompting the user to enter the numbers of a sudoku puzzle, with 0 for blanks.
		sudoku() {
			char copt;
			int iopt = 0;

			while (iopt < 1 || iopt > 3) {
				cout << endl << "Enter an option:" << endl << endl;
				cout << "(1) Choose an easy puzzle." << endl;
				cout << "(2) Choose a hard puzzle." << endl;
				cout << "(3) Enter a puzzle." << endl << endl;
				cout << "Option: ";
				cin >> copt;
				iopt = convert(copt);
			}
	
			//Random variable to generate one of the boards
			int randBoard;
			srand(time(NULL));
			randBoard = rand() % 9;

			//Easy Board
			if (iopt == 1) {
				//All the easy boards that may be generated.
				int easy[9][9][9] = {{{0,6,0,3,7,8,0,0,5}, {0,0,4,0,0,1,9,2,0}, {0,8,5,4,0,0,7,0,3}, {0,3,0,0,0,4,0,7,0}, {6,4,9,2,0,7,8,0,0}, {0,0,7,6,0,0,0,0,0}, {2,0,8,7,0,5,0,9,6}, {4,0,0,0,0,0,0,5,0}, {0,5,3,1,9,0,2,0,0}},
									{{3,4,0,0,0,0,0,7,0}, {8,0,0,4,0,7,2,5,0}, {7,0,6,8,0,0,3,0,9}, {0,1,3,0,0,6,4,0,0}, {0,0,7,0,0,4,0,1,0}, {0,0,4,0,0,0,6,0,3}, {0,7,9,6,5,0,1,0,2}, {0,0,0,7,0,0,5,9,8}, {0,3,0,2,9,1,7,0,0}},
									{{0,3,1,6,7,0,4,0,9}, {0,0,0,8,3,0,0,0,0}, {8,2,0,0,0,0,0,1,0}, {0,7,4,0,0,8,1,6,0}, {0,8,0,0,6,0,0,0,4}, {9,0,2,0,0,0,0,7,3}, {4,9,0,0,5,7,2,3,0}, {2,0,0,0,9,0,5,0,7}, {7,0,3,2,0,0,6,0,1}},
									{{0,2,1,0,0,4,8,3,0}, {4,0,3,5,0,8,2,0,1}, {0,6,0,1,3,0,0,0,0}, {0,9,2,0,7,0,5,4,0}, {1,0,5,3,0,0,0,0,0}, {0,0,7,0,0,0,0,0,8}, {0,5,0,0,2,0,3,0,0}, {2,3,0,0,0,0,0,8,6}, {7,1,0,6,8,3,4,5,0}},
									{{0,4,0,9,0,9,3,8,0}, {6,0,0,0,0,0,0,9,0}, {2,9,0,3,7,4,5,0,0}, {0,1,7,0,9,6,0,2,3}, {0,0,0,2,0,0,0,5,4}, {8,0,4,0,0,0,0,0,0}, {0,0,2,5,3,0,9,0,8}, {4,0,0,0,2,7,6,0,1}, {0,8,1,0,0,0,2,7,0}},
									{{0,0,1,0,5,4,0,0,0}, {3,4,0,0,0,0,0,0,1}, {2,0,0,0,1,9,0,7,0}, {4,0,7,9,3,1,0,6,0}, {9,1,0,0,7,0,3,4,0}, {0,0,0,2,0,5,0,0,7}, {1,3,2,0,9,7,0,0,5}, {0,6,4,5,0,0,0,1,0}, {0,0,8,1,0,6,0,0,4}},
									{{0,8,4,0,0,2,0,3,0}, {2,0,7,8,3,1,0,0,9}, {0,1,0,5,0,0,0,2,7}, {0,7,8,0,1,0,9,0,2}, {0,0,9,7,6,0,0,8,5}, {5,0,1,9,0,0,3,0,0}, {0,3,0,1,0,7,4,0,6}, {0,0,6,2,0,0,0,0,0}, {7,0,0,3,9,0,0,0,0}},
									{{5,0,0,0,0,0,0,0,9}, {0,4,0,0,1,5,0,8,0}, {0,0,7,0,0,3,4,5,2}, {2,1,0,7,6,0,0,3,0}, {0,0,4,0,9,8,2,6,1}, {0,0,0,0,3,2,0,0,4}, {9,0,6,0,7,1,0,0,3}, {8,0,1,0,4,0,0,2,7}, {0,0,3,0,0,0,0,9,8}},
									{{0,6,2,3,0,8,4,0,0}, {1,8,5,0,2,0,7,0,3}, {0,7,0,0,0,1,0,0,0}, {0,0,0,0,4,5,3,9,6}, {0,9,0,0,0,0,1,0,7}, {7,0,0,0,9,6,2,8,0}, {5,3,1,9,0,0,6,0,0}, {0,4,9,0,5,0,0,0,1}, {0,2,0,6,0,0,0,4,0}}};

				for(int i = 0; i < 9; i++) {
					for(int j =0; j < 9; j++) {
						grid[i][j] = easy[randBoard][i][j];
					}
				}

			//Hard Board
			} else if (iopt == 2) {
				//All the hard boards that may be randomly generated.
				int hard[9][9][9] = {{{0,0,9,0,7,0,0,0,0}, {0,8,0,4,0,0,0,0,0}, {0,0,3,0,0,0,0,2,8}, {1,0,0,0,0,0,6,7,0}, {0,2,0,0,1,3,0,4,0}, {0,4,0,0,0,7,8,0,0}, {6,0,0,0,3,0,0,0,0}, {0,1,0,0,0,0,0,0,0}, {0,0,0,0,0,0,2,8,4}},	
									{{0,0,0,9,1,0,0,0,0}, {9,0,0,6,0,0,3,0,0}, {0,8,3,0,5,0,0,7,0}, {0,0,0,0,0,0,0,0,5}, {0,0,0,0,0,0,0,0,0}, {2,0,0,0,0,1,4,0,7}, {1,0,2,0,7,0,6,0,0}, {0,0,4,0,0,0,2,9,0}, {0,0,0,0,6,0,0,0,0}},
									{{0,0,0,0,6,0,2,0,7}, {0,7,8,0,0,0,0,0,0}, {0,0,5,0,0,0,0,0,0}, {0,9,0,0,0,0,0,0,0}, {0,2,0,7,3,0,0,5,0}, {0,0,0,2,0,9,0,7,0}, {0,0,0,9,0,6,0,0,0}, {0,0,0,0,5,0,4,3,0}, {8,0,0,4,0,0,5,2,0}},
									{{0,0,5,0,7,0,2,0,6}, {0,0,3,0,2,0,5,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,6,0,4,5,0,0,0}, {0,0,0,0,0,0,0,0,9}, {0,0,0,1,0,0,3,7,0}, {7,0,0,9,0,0,0,0,0}, {0,8,0,2,0,0,0,6,0}, {4,0,0,0,0,3,0,8,0}},
									{{0,0,0,0,0,0,0,0,2}, {0,0,1,0,0,6,0,0,5}, {3,0,0,0,0,4,0,0,0}, {2,9,0,4,0,0,3,0,0}, {0,0,0,0,2,0,0,6,1}, {5,0,0,7,0,0,0,0,0}, {0,5,0,0,0,0,9,0,0}, {9,0,4,0,0,1,0,5,0}, {7,0,0,0,0,0,0,0,3}},
									{{9,0,0,6,0,5,1,0,0}, {0,0,0,0,0,0,0,0,0}, {8,0,0,0,1,0,0,0,0}, {0,0,0,9,0,0,0,0,0}, {6,2,7,0,0,0,0,4,0}, {0,0,0,0,0,3,0,0,6}, {0,1,0,0,6,0,4,2,0}, {4,0,0,0,0,7,0,8,0}, {7,0,0,3,0,0,0,1,0}},
									{{0,0,0,6,5,0,0,0,0}, {0,0,8,4,0,0,9,1,0}, {0,0,0,0,0,0,0,8,3}, {0,6,0,0,0,0,0,0,0}, {3,5,0,0,0,0,0,0,1}, {0,1,9,7,0,0,0,5,0}, {0,0,7,0,0,0,0,0,2}, {1,0,0,0,0,0,0,0,0}, {0,0,0,0,2,9,7,6,0}},
									{{0,0,4,0,0,0,0,5,7}, {0,0,0,0,0,0,3,9,0}, {0,0,0,1,0,6,0,0,0}, {1,0,5,9,0,0,0,0,0}, {9,4,0,2,0,0,0,0,1}, {0,0,0,0,0,3,0,0,0}, {2,6,0,0,0,8,0,0,0}, {0,8,0,0,0,0,7,0,0}, {0,0,0,5,0,0,0,2,0}},
									{{5,0,0,0,3,2,0,0,0}, {0,0,0,0,7,0,0,0,0}, {0,0,4,0,0,0,3,5,0}, {4,0,0,6,0,0,0,0,0}, {0,0,0,2,5,0,9,0,6}, {7,0,0,9,0,0,1,0,0}, {0,0,0,0,0,0,0,0,0}, {2,0,8,5,0,0,0,7,0}, {0,0,3,0,0,9,0,8,0}}};
				
				for(int i = 0; i < 9; i++) {
					for(int j =0; j < 9;  j++) {
						grid[i][j] = hard[randBoard][i][j];
					}
				}

			//Enter own board
			} else {

				//The users is prompter to enter the puzzle row by row.
				cout << endl << "Enter each row of the puzzle starting from the top going down and entries from left to right." << endl;
				cout << "Only use digits 1-9 and 0 if blank." << endl << endl;
				cout << "Example 1: 1 0 0 4 2 0 9 0 8" << endl;
				cout << "Example 2: 100850640" << endl;
				cout << "Example 3: 0, 1, 0, 6, 0, 0, 0, 3, 7" << endl << endl << endl;

				// For loop iterating through each row.
				for (int i = 0; i < 9; i++)	{
					bool validInput = false;
					int rowInput[9] = {0,0,0,0,0,0,0,0,0};

					//Input validition.
					while(!validInput) {
						string in;
						int count = 0;
						getline(cin, in);

						//Iterates through input. If it is a digit it is added to an array.
						for (int k = 0; k < in.size() && count < 9; k++) {
							if(isdigit(in[k])) {
								rowInput[count] = in[k] -48;
								count++;
							}
						}
						
						//If input was valid then loop is ended.
						if(count == 9) {
							validInput = true;
						}
					}

					//Values are given to grid.
					cout<<endl << endl << setw(5) <<" row " << setw(5) << " col: " << setw(5) << " value ";

					for(int j = 0; j < 9; j++){
						grid[i][j] = rowInput[j];
						cout << endl <<  setw(3) << i <<  setw(5) <<j << ": " << setw(5) << grid[i][j];
					}
					cout << endl << endl;		
				}
			}
		}

		//Input: A possible value of a cell, the uppermost row of the cell's unit, and its leftmost column of the unit.
		//Output: Boolean where true means value has not be assigned to unit, false otherwise
		bool unitValid(int startRow, int startColumn, int value) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (grid[startRow + i][startColumn + j] == value) {
						return false;
					}
				}
			}
			return true;
		}

		//Input: A possible value of cell and its row.
		//Output: Determines if value has been assigend to row or not.
		bool rowValid(int row, int value) {
			for (int i = 0; i < 9; i ++) {
				if (grid[row][i] == value) {
					return false;
				}
			}
			return true;
		}

		//Input: A possible value for cell and its column.
		//Output Determines if value has been assigned to column.
		bool columnValid(int col, int value) {
			for (int i = 0; i < 9; i++) {
				if (grid[i][col] == value) {
					return false;
				}
			}
				return true;
		}

		//Input: Value for cell, its row, its column.
		//Output: True if there is no conflicts with the cell's value and any other value in its row, column and unit.
		bool cellValid(int row, int col, int value) {
			return unitValid(row - row % 3, col - col % 3, value) && rowValid(row, value) && columnValid(col, value); 
		}

		//Runs two loops through the grid to determine if there are any 0's (or unassigned cells) in the grid.
		bool emptyCells() {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (grid[i][j] == 0) {
						return true;
					}
				}
			}
			return false;
		}

		//Using nested loops finds the row number of the first instance of a 0 or unassigned value. If there is none then function returns 9.
		int emptyRow() {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (grid[i][j] == 0) {
						return i;
					}
				}
			}
			return 9;
		}

		//Using nested loops finds the column number of the first instance of a 0 or unassigned value. If there is none then function returns 9.
		int emptyColumn() {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (grid[i][j] == 0) {
						return j;
					}
				}
			}
			return 9;
		}

		//Displays the grid
		void display() {
			cout << endl << endl << setw(4) << " ";

			//Displays column headers.
			for (int j = 0; j < 9; j++)	{
		    	if (j % 3 ==0) {
        		    cout << setw(4) << left << " ";
        		}
				cout << setw(4) << j + 1;
			}

			//Horizontal line dividing every third row.
			for (int i = 0; i < 9; i++) { 
				if (i % 3 == 0)	{
    				cout << endl <<	setw(4) << " " << "-------------------------------------------------" << endl << endl;
        		} else {
        		    cout << endl << endl;
				}

				cout << setw(4) << left << i + 1;

				//Prints each cell in a row
				for (int j = 0; j < 9; j++)	{
		            if (j % 3 ==0) {
        		        cout << setw(4) << left << "|";
        		    }

					if (0 == grid[i][j]) {
						cout << setw(4) << " ";
					} else {
						cout << setw(4) << grid[i][j];
					}
				}
				cout << setw(4) << "|" ;
			}
			cout << endl << endl << setw(4) << " " << "-------------------------------------------------" << endl ;
		}

		//Using the backtrack method solves puzzle otherwise returns false if it cannot e solved.
		bool solve() {

			// First it determines if all the cells are filled in or not. If so then the puzzle is solved.
			if (!emptyCells()) {
				return true;
			}

			int x = emptyColumn();
			int y = emptyRow();

			//If it is not solved yet then it begins a loop. Starting with one and for the first empty cell, it is determined if there are any conflicts with the assignment.
			// If there is conflict then the value is increased by one until reaching 9.
			for (int value = 1; value <= 9; value++) {
				if (cellValid(y, x, value)) {

					//If there is no conflict, then the value is assigned to the cell.
					grid[y][x] = value;

					// A recursion is started and contiues until either all the cells are filled returning true or until a conflict occurs and false is return.
					if (solve()) {
						return true;
					}

					// If a false is return from the recursion then the most current cell being worked on is assigned a value of 0 to continue the loop.
					grid[y][x] = 0;
				}
			}

			// When following a branch, if no solution is found then it will return false and continue on in the loop into another branch.
			// Hhowever, if this is the last branch being investigated and returns false, then the whole puzzle has no solution.
			return false;
		}

		//Input: Row and column number of a specified cell.
		//Output: Returns the value of the cell.
		int hint(int row, int column) {
			solve();
			return grid[row-1][column-1];	
		}

		//Input: Row and column number of a specified cell and a value to compare it against.
		//output: Boolean determining if a given value matches the value of a specified cell.
		bool check(int row, int column, int value) {
			solve();
			return (grid[row-1][column-1] == value);
		}
};


//Prompts the user to choose an action.
int menuA() {
	char copt;
	int iopt = 0;

     while (iopt < 1 || iopt > 4) {
        cout << endl << endl << "Choose an option:" << endl;
	    cout << "(1) Solve puzzle." << endl;
	    cout << "(2) Give hint." << endl;
        cout << "(3) Determine if puzzle may be solved." << endl;
        cout << "(4) See if possible assignment is correct." << endl << endl;
		cout << "Option: ";
        cin >> copt;
		iopt = convert(copt);
    }
	return iopt;
}

//Solve and displays the solution.
void menuB1(sudoku puzzle) {
	puzzle.solve();
	puzzle.display();
}

//If option 2 is choosen then the user is prompeted to give the row and column numbers of the desired cell.
void menuB2(sudoku puzzle) {
	char crow, ccol;
	int irow, icol = 10;

	while(irow < 1 || irow > 9) {
		cout << endl << endl << "Enter the row number (1-9)" << endl << endl;
		cout << "Row: ";
		cin >> crow;
		irow = convert(crow);
	}

	while(icol < 1 || icol > 9 ) {
		cout << endl << endl << "Enter the column number (1-9)" << endl << endl;
		cout << "Column: ";
		cin >> ccol;
		icol = convert(ccol);
	}
	cout << endl << "Hint: " << puzzle.hint(irow, icol) << endl;
}

// Option 3 displays whether the puzzle may be solved or not.
void menuB3(sudoku puzzle) {
	if (puzzle.solve()) {
		cout << endl << endl << "The puzzle has a solution" << endl;
	} else {
		cout << endl << endl << "The puzzle has no solution"  << endl;
	}
}

// The last option checks if a given value matches the actual value	
void menuB4(sudoku puzzle) {
	char crow, ccol, cval;
	int irow, icol, ival = 10;

	while(irow < 1 || irow > 9) {
		cout << endl << endl << "Enter the row number (1-9)" << endl << endl;
		cout << "Row:";
		cin >> crow;
		irow = convert(crow);
	}

	while(icol < 1 || icol > 9 ) {
		cout << endl << endl <<"Enter the column number (1-9)" << endl << endl;
		cout << "Column: ";
		cin >> ccol;
		icol = convert(ccol);
	}

	while(ival < 1 || ival > 9 ) {
		cout << endl << endl << "Enter the value (1-9)" << endl << endl;
		cout << "Value: ";
		cin >> cval;
		ival = convert(cval);
	}
		
	if (puzzle.check(irow, icol, ival)) {
		cout << endl << endl << "The value is correct" << endl;
	} else {
		cout << endl << endl << "The value does not match" << endl;
	}
}

//Provides results for the ac<tion choosen and additional prompts.
void menuB(int option, sudoku puzzle) {
	if (option == 1) {
		menuB1(puzzle);
    } else if (option == 2) {
		menuB2(puzzle);
    } else if (option == 3) {
		menuB3(puzzle);
    } else {
		menuB4(puzzle);
	} 
}

//Prompts user to continue the program or not
bool menuC() {	
	char copt;
	int iopt = 0;

    while (iopt < 1 || iopt > 2) {
        cout << endl << endl << "Continue the program?" << endl;
       	cout << "(1) yes " << endl;
       	cout << "(2) no " << endl << endl;
		cout << "Option: ";
        cin >> copt;
		iopt = convert(copt);
    }
	
	if(iopt == 1) {
		return true;
	} else {
		return false;
	}
	cout << endl << endl << endl;
}

// Cylces through the actions as long as the users would like to.
void menu(sudoku puzzle) {
	bool continue_ = true;
	int option = 0;

    while (continue_) {
        menuB(menuA(), puzzle);
        continue_ = menuC();
	}
}

//Finally, run the program.
int main() {
	sudoku puzzle;
	puzzle.display();
	menu(puzzle);
}