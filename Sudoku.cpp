#include "Sudoku.h"
#include <iostream>

Sudoku::Sudoku() : 
	_gridDim(0), _boardDim(0), _sudokuBoard(nullptr) {}

Sudoku::Sudoku(int gridDim, int* values)
{
	_gridDim = gridDim;
	_boardDim = _gridDim * _gridDim;

	_sudokuBoard = new int[_boardDim * _boardDim];

	for (int i = 0; i < _boardDim * _boardDim; i++)
		_sudokuBoard[i] = values[i];
}

Sudoku::Sudoku(const Sudoku& other) : 
	_gridDim(other._gridDim), _boardDim(other._boardDim) 
{
	_sudokuBoard = new int[_boardDim * _boardDim];
	for (int i = 0; i < _boardDim * _boardDim; ++i)
		_sudokuBoard[i] = other._sudokuBoard[i];
}

void Sudoku::Print()
{
	for (int i = 0; i < _boardDim; i++)
	{
		for (int j = 0; j < _boardDim; j++)
		{
			if (_sudokuBoard[_boardDim * i + j] != 0)
				std::cout << _sudokuBoard[_boardDim * i + j] << " ";
			else
				std::cout << "_ ";

			if ((j + 1) % _gridDim == 0 && j + 1 < _boardDim)
				std::cout << "| ";
		}

		std::cout << std::endl;

		if ((i + 1) % _gridDim == 0 && i + 1 < _boardDim)
		{
			for (int j = 0; j < _boardDim + _gridDim - 1; j++)
				std::cout << "--";
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}