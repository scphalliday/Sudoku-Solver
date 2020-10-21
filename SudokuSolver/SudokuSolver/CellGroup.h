#pragma once
#include "Cell.h"
class CellGroup
{
public:
	CellGroup(void);
	~CellGroup(void);

	//methods
	//setter
	void SetCell(const int index, Cell* const cell) {
		cells[index] = cell;
	}	
	//getter
	Cell * GetCell(int index) const;

private:
	//variables
	Cell* cells[9];
};

