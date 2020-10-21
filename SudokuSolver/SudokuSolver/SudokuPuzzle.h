#pragma once
#include "CellGroup.h"
using namespace std;

class SudokuPuzzle {
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	//methods
	void solve(char filenameIn[]);

private:
	//private methods
	void output() const;
	void readPuzzle(char filenameIn[]);
	const CellGroup& GetCellBlock(const int pstart, const int pend, CellGroup* CellBlock) const;
	const CellGroup& CandidateSearch(const int rstart, const int cstart, CellGroup* GridBlocks, bool* solved, int* numOfSolvedCells, bool* gridChangeMade, int* numOfPossibleCandidates) const;
	//variables
	CellGroup gridRows[9];
	CellGroup gridColumns[9];
	CellGroup gridBlocks[9];
};

//unused method, see cpp for details
//const CellGroup& hiddenSinglesMethod(const int rstart, const int cstart, CellGroup* GridBlocks) const;
