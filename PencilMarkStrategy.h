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
	void CheckRow(int i, int index);
	void CheckColumn(int j, int index);
	void CheckGrid(int k, int index);
};