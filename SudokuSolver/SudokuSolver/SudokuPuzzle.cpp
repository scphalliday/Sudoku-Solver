#include "SudokuPuzzle.h"
#include "CellGroup.h"
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

SudokuPuzzle::SudokuPuzzle() {
}
SudokuPuzzle::~SudokuPuzzle() {
}

void SudokuPuzzle::solve(char filenameIn[]) {
	// Read puzzle from text file
	readPuzzle(filenameIn);

	// Get start time
	const auto startTime = std::chrono::high_resolution_clock::now();

	//code to solve the puzzle
	bool solved = true;
	int numOfPasses = 0;
	int numOfSolvedCells = 0;
	bool gridChangeMade = false;
	int numOfPossibleCandidates = 0;
	do {			//selecting the blocks of cells as a starting point to iterate the grid
		++numOfPasses;
		solved = true;
		gridChangeMade = false;
		int index = 0;
		int rowStart = 0;
		for (int rowBlock = 0; rowBlock < 3; ++rowBlock) {
			int columnStart = 0;
			for (int columnBlock = 0; columnBlock < 3; ++columnBlock) {
				gridBlocks[index] = CandidateSearch(rowStart, columnStart, &gridBlocks[index], 
					&solved, &numOfSolvedCells, &gridChangeMade, &numOfPossibleCandidates);
				columnStart += 3;
				++index;
			}
			rowStart += 3;
		}
		if (!gridChangeMade && !solved) //used to break out the loop if the puzzle is not solved
		{
			cout << "Puzzle not solvable with naked singles algorithm." << endl;
			break;
		}
	} while (!solved);

	// Get end time
	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto duration = (endTime - startTime).count();

	// timing output in nanoseconds
	cout << "Time taken in nanoseconds: " << duration << "ns" << endl;
	cout << "Number of grid iterations using naked singles algorithm: " << numOfPasses << endl;
	cout << "Number of cells solved not including pre-set cells: " << numOfSolvedCells << endl;
	cout << "Number of possible candidate values considered: " << numOfPossibleCandidates << endl;
	if (numOfSolvedCells > 0) {
		cout << "An average of " << numOfPossibleCandidates / numOfSolvedCells << " candidates per cell. (discarding decimal place)" << endl;
	}

	// Output the solved puzzle
	output();
}

void SudokuPuzzle::readPuzzle(char filenameIn[]) {

	ifstream fin(filenameIn);

	//filling rows with new cell objects. 81 in total
	for (int row = 0; row < 9; ++row){
		for (int column = 0; column < 9; column++){
			int inputValue;
			bool inputBool = false;
			fin >> inputValue;
			if (inputValue != 0){
				inputBool = true;
			}
			gridRows[row].SetCell(column, new Cell(inputValue, inputBool)); //creating new cell objects
		}
	}

	//filling columns with pointers to cells objects created within the rows
	for (int column = 0; column < 9; ++column){ 
		for (int row = 0; row < 9; row++)
		{
			gridColumns[column].SetCell(row, gridRows[row].GetCell(column));
		}
	}

	//setting gridBlocks
	int index = 0;
	int rowStart = 0;
	for (int rowBlock = 0; rowBlock < 3; ++rowBlock) {
		int columnStart = 0;
		for (int columnBlock = 0; columnBlock < 3; ++columnBlock){
			gridBlocks[index] = GetCellBlock(rowStart, columnStart, &gridBlocks[index]);
			columnStart += 3;
			++index;
		}
		rowStart += 3;
	}
}
//method called to handle the block of a cell. which block depicted by starting row and column
const CellGroup& SudokuPuzzle::GetCellBlock(const int Rstart,const int Cstart, CellGroup* const GridBlocks) const{
	const int RowRtart = Rstart;
	const int ColumnStart = Cstart;
	int index = 0;
	for (int row = RowRtart; row < RowRtart + 3; ++row){
		for (int column = ColumnStart; column < ColumnStart + 3; ++column){
			GridBlocks->SetCell(index, gridRows[row].GetCell(column));
			++index;
		}
	}
	return *GridBlocks;
}

const CellGroup& SudokuPuzzle::CandidateSearch(const int Rstart, const int Cstart, CellGroup* const GridBlocks,
		bool* const solved, int* const numOfSolvedCells, bool* const gridChangeMade, int* const numOfPossibleCandidates) const{
	const int RowStart = Rstart;
	const int ColumnStart = Cstart;
	int index = 0;
	for (int row = RowStart; row < RowStart + 3; ++row) {
		for (int column = ColumnStart; column < ColumnStart + 3; ++column) {
			if (!GridBlocks->GetCell(index)->getGiven()){
				*solved = false;
				vector<int> templist = GridBlocks->GetCell(index)->getCandidateList();
				for (int listIndex = 0; listIndex < templist.size(); ++listIndex){
					for (int rowIndex = 0; rowIndex < 9; ++rowIndex){
						if (templist[listIndex] == gridRows[row].GetCell(rowIndex)->getValue()){
							GridBlocks->GetCell(index)->delCandidate(templist[listIndex]);
							*gridChangeMade = true;
						}
					}
					for (int columnIndex = 0; columnIndex < 9; ++columnIndex) {
						if (templist[listIndex] == gridColumns[column].GetCell(columnIndex)->getValue()) {
							GridBlocks->GetCell(index)->delCandidate(templist[listIndex]);
							*gridChangeMade = true;
						}
					}
					for (int blockIndex = 0; blockIndex < 9; ++blockIndex) {
						if (templist[listIndex] == GridBlocks->GetCell(blockIndex)->getValue()){
							GridBlocks->GetCell(index)->delCandidate(templist[listIndex]);
							*gridChangeMade = true;
						}
					}
				}
				*numOfPossibleCandidates += gridBlocks->GetCell(index)->getCandidateLength();
				if (GridBlocks->GetCell(index)->getCandidateList().size() == 1){
					GridBlocks->GetCell(index)->SetValue(GridBlocks->GetCell(index)->getCandidateList()[0]);
					GridBlocks->GetCell(index)->setGiven(true);
					*gridChangeMade = true;
					*numOfSolvedCells += 1;
				}
			}
			++index;
		}
	}
	return *GridBlocks;
}

void SudokuPuzzle::output() const {
	ofstream fout("sudoku_solution.txt");
	for (int row = 0; row < 9; ++row){
		for (int column = 0; column < 9; ++column){
			fout << gridRows[row].GetCell(column)->getValue() << " ";
			cout << gridRows[row].GetCell(column)->getValue() << " ";
		}
		fout << endl;
		cout << endl;
	}
}

//variables
CellGroup gridRows[9];
CellGroup gridColumns[9];
CellGroup gridBlocks[9];




//unused code
//this method was unused. more experimental time is needed before this method can be implemented
//does not currently work as intended, and even if it did, is VERY ineffecient.
//method would have been called the same as the candidate search method. 

//const CellGroup& SudokuPuzzle::hiddenSinglesMethod(const int rstart, const int cstart, CellGroup* GridBlocks) const{
//	const int RowStart = rstart;
//	const int ColumnStart = cstart;
//	int index = 0;
//	for (int row = RowStart; row < RowStart + 3; ++row){
//		for (int column = ColumnStart; column < ColumnStart + 3; ++column){
//			if (!GridBlocks->GetCell(index)->getGiven()) {
//				vector<int> templist = GridBlocks->GetCell(index)->getCandidateList();
//				for (int listIndex = 0; listIndex < templist.size(); ++listIndex){
//					bool sameValueFound = false;
//					for (int rowIndex = 0; rowIndex < 9; ++rowIndex){
//						vector<int> tempCand = gridRows->GetCell(rowIndex)->getCandidateList();
//						for (int currentCandidate = 0; currentCandidate < tempCand.size(); ++currentCandidate){
//							if (templist[listIndex] == tempCand[currentCandidate]);{
//								sameValueFound = true;
//							}
//						}
//					}
//					for (int columnIndex = 0; columnIndex < 9; ++columnIndex){
//						vector<int> tempCand = gridColumns->GetCell(columnIndex)->getCandidateList();
//						for (int currentCandidate = 0; currentCandidate < tempCand.size(); ++currentCandidate){
//							if (templist[listIndex] == tempCand[currentCandidate]);{
//								sameValueFound = true;
//							}
//						}
//					}
//					for (int blocknIndex = 0; blocknIndex < 9; ++blocknIndex){
//						vector<int> tempCand = gridBlocks->GetCell(index)->getCandidateList();
//						for (int currentCandidate = 0; currentCandidate < tempCand.size(); ++currentCandidate){
//							if (templist[listIndex] == tempCand[currentCandidate]);{
//								sameValueFound = true;
//							}
//						}
//					}
//					if (!sameValueFound){
//						GridBlocks->GetCell(index)->SetValue(templist[listIndex]);
//						GridBlocks->GetCell(index)->setGiven(true);
//
//					}
//				}
//			}
//			++index;
//		}
//	}
//	return *GridBlocks;
//}