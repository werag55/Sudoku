#pragma once

class Sudoku
{
public:
	int _gridDim;		// dimension of the single grid of the sudoku board
	int _boardDim;		// dimension of the sudoku board

	int* _sudokuBoard;  // 1D array representation of the sudoku puzzle

	Sudoku();
	Sudoku(int gridDim, int* sudokuBoard);
	Sudoku(const Sudoku& other);
	void Print();
};