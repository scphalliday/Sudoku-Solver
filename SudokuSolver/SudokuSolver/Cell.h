#pragma once
#include <vector>
using namespace std;
class Cell
{
public:
	Cell(const int pvalue,const bool pgiven);
	~Cell(void);

	//methods
	//getters
	int getValue() const {
		return value;
	}
	bool getGiven() const {
		return given;
	}
	int getCandidateLength() const {
		return candidateList.size();
	}
	const vector<int> &getCandidateList() const
	{
		return candidateList;
	}
	//setters
	void SetValue(const int pvalue) {
		value = pvalue;
	}
	void setGiven(const bool pgiven) {
		given = pgiven;
	}

	void addCandidate(const int pvalue) {
		candidateList.push_back(pvalue);
	}	
	void delCandidate(int value);

private:
	vector<int> candidateList;
	int value;
	bool given;
};

                        