#pragma once
#include "Sudoku.h"

class PencilMark
{
	Sudoku _sudoku;      // the sudoku puzzle that is being solved
	bool** _pencilMarks; // an array that for each field on the sudoku board stores an array that
						 // for every possible value determines if it is possible to placed it there
	int _maxIter; // maximum number of iterations

public:
	PencilMark(const Sudoku& sudoku, int maxIter = 500);
	Sudoku Solve();


private:
	int CountFixedValues();
	void CheckRow(int i, int index);
	void CheckColumn(int j, int index);
	void CheckGrid(int indexI, int indexJ);
	int TryToMark(int index);
};