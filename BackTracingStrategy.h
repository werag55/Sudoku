#pragma once
#include "Sudoku.h"

class BackTracing
{
	Sudoku _sudoku;

	// hash table use to check duplicates in row column or grid 
	bool* HashTable;

public:
	BackTracing(const Sudoku& sudoku);
	Sudoku Solve();
	

private:
	
	bool CheckRow(int i);
	bool CheckColumn(int j);
	bool CheckGrid(int indexI, int indexJ);
	bool IsValid();
	bool Solving(int i, int j);
};