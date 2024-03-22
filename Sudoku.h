#pragma once
#include <vector>

class Sudoku
{
public:
	int _gridDim;		// dimension of the single grid of the sudoku board
	int _boardDim;		// dimension of the sudoku board

	int* _sudokuBoard;  // 1D array representation of the sudoku puzzle

	std::vector<int>* _IndexesByGrid; // tablice indeksów znajdujacych sie w danym gridzie

	Sudoku();
	Sudoku(int gridDim, int* sudokuBoard);
	Sudoku(const Sudoku& other);
	void Print();
	static int WhichGrid(int index);  // which grid is it?
	
};