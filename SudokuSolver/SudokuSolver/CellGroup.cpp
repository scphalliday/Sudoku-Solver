#include "CellGroup.h"
#include "Cell.h"
using namespace std;

CellGroup::CellGroup(void):cells(){
}
CellGroup::~CellGroup(void){
	for (int i = 0; i < 9; ++i) {
		if (!cells) {
			delete cells[i];
			cells[i] = nullptr;
		}
	}
}
//methods
Cell * CellGroup::GetCell(int index) const{
	return cells[index];
}
//variables
Cell* cells[];