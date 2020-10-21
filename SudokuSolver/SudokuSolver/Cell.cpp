#include "Cell.h"

Cell::Cell(const int pvalue, const bool pgiven)
		:value(pvalue), given(pgiven){  //initalizer list
	if (!pgiven) {
		for (int i = 1; i < 10; ++i) {
			candidateList.push_back(i);  //cells with a 0 value, cells not set, been given candidate lists
		}
	}
}
Cell::~Cell(void){
}

//methods
void Cell::delCandidate(const int pvalue) {
	for (int i = 0; i < candidateList.size() ; ++i) {		//looping through the list to find the value element to delete
		if (candidateList[i] == pvalue) {
			candidateList.erase(candidateList.begin() + i); //once found, removing from the index of the beginning + the index of the element to delete
		}
	}
}

//variables
vector<int> candidateList;   //list of possible candidates for answers
int value;					//value of the cell
bool given;					//indicates whether the value was given by the input file or not