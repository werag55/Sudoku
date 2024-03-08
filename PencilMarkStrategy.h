#pragma once
#include "Sudoku.h"

class PencilMark
{
	Sudoku _sudoku;
	bool** _pencilMarks;

public:
	PencilMark(const Sudoku& sudoku);
	Sudoku Solve();

private: 
	int CountFixedValues();
	void CheckRow(int i, int index);
	void CheckColumn(int j, int index);
	void CheckGrid(int indexI, int indexJ);
	int TryToMark(int index);
};