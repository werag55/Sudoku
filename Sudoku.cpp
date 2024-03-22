#include "Sudoku.h"
#include <iostream>

/// <summary>
/// Default constructor for Sudoku. Initializes grid dimensions and sudoku board to null.
/// </summary>
Sudoku::Sudoku() :
	_gridDim(0), _boardDim(0), _sudokuBoard(nullptr) {}

/// <summary>
/// Constructor for Sudoku with specified grid dimensions and values.
/// </summary>
/// <param name="gridDim">The dimension of the grid.</param>
/// <param name="values">An array containing the initial values of the sudoku puzzle.</param>
Sudoku::Sudoku(int gridDim, int* values)
{
	_gridDim = gridDim;
	_boardDim = _gridDim * _gridDim;

	_IndexesByGrid = new std::vector<int>[_boardDim];

	// inicjalizacja indeksow
	for (int i = 0; i < _boardDim * _boardDim; i++)
	{
		_IndexesByGrid[Sudoku::WhichGrid(i)].push_back(i);
	}

	_sudokuBoard = new int[_boardDim * _boardDim];

	for (int i = 0; i < _boardDim * _boardDim; i++)
		_sudokuBoard[i] = values[i];
}

/// <summary>
/// Copy constructor for Sudoku.
/// </summary>
/// <param name="other">The Sudoku object to copy.</param>
Sudoku::Sudoku(const Sudoku& other) :
	_gridDim(other._gridDim), _boardDim(other._boardDim)
{
	_IndexesByGrid = other._IndexesByGrid;

	_sudokuBoard = new int[_boardDim * _boardDim];
	for (int i = 0; i < _boardDim * _boardDim; i++)
		_sudokuBoard[i] = other._sudokuBoard[i];
}

/// <summary>
/// Prints the sudoku puzzle to the console.
/// </summary>
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
	std::cout << std::endl << std::endl;
}

/// <summary>
///  Index of Grid base on index
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
int Sudoku::WhichGrid(int index)
{
	int i = (index / 9) / 3;
	int j = (index % 9) / 3;

	int grid = i * 3 + j;

	return grid;
}