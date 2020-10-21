#include "SudokuPuzzle.h"
using namespace std;

int main(const int argc, char **) {
	SudokuPuzzle puzzle;
	char filename[] = "sudoku_puzzle.txt";
	puzzle.solve(filename);
	system("pause");
	return 0;
}
