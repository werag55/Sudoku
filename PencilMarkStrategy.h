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
	void CheckRow(int i);
	void CheckColumn(int j);
	void CheckGrid(int k);
};