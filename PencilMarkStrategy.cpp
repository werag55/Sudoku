#pragma once

#include "PencilMarkStrategy.h"

/// <summary>
/// Constructs the PencilMark object with the given sudoku puzzle.
/// </summary>
/// <param name="sudoku">The sudoku puzzle to solve.</param>
PencilMark::PencilMark(const Sudoku& sudoku)
{
	_sudoku = Sudoku(sudoku);

	_pencilMarks = new bool* [_sudoku._boardDim * _sudoku._boardDim];
	for (int i = 0; i < _sudoku._boardDim * _sudoku._boardDim; i++)
	{
		_pencilMarks[i] = new bool[_sudoku._boardDim];

		for (int j = 0; j < _sudoku._boardDim; j++)
			_pencilMarks[i][j] = true;
	}
}

/// <summary>
/// Counts the number of fixed values (non-zero) in the sudoku puzzle.
/// </summary>
/// <returns>The number of fixed values in the puzzle.</returns>
int PencilMark::CountFixedValues()
{
	int ret = 0;

	for (int i = 0; i < _sudoku._boardDim * _sudoku._boardDim; i++)
		if (_sudoku._sudokuBoard[i] != 0)
			ret++;

	return ret;
}

/// <summary>
/// Checks and updates pencil marks for a specific field based on the values in the row where the field is located.
/// </summary>
/// <param name="i">Row index to check.</param>
/// <param name="index">Index of the field in the 1D array representation of the sudoku puzzle.</param>
void PencilMark::CheckRow(int i, int index)
{
	for (int j = 0; j < _sudoku._boardDim; j++)
	{
		int val = _sudoku._sudokuBoard[_sudoku._boardDim * i + j];
		if (val != 0)
			_pencilMarks[index][val - 1] = false;
	}
}

/// <summary>
/// Checks and updates pencil marks for a specific field based on the values in the column where the field is located.
/// </summary>
/// <param name="j">Column index to check.</param>
/// <param name="index">Index of the field in the 1D array representation of the sudoku puzzle.</param>
void PencilMark::CheckColumn(int j, int index)
{
	for (int i = 0; i < _sudoku._boardDim; i++)
	{
		int val = _sudoku._sudokuBoard[_sudoku._boardDim * i + j];
		if (val != 0)
			_pencilMarks[index][val - 1] = false;
	}
}

/// <summary>
/// Checks and updates pencil marks for a specific field based on the values in the grid where the field is located.
/// </summary>
/// <param name="indexI">Row index of the field</param>
/// <param name="indexJ">Column index of the field.</param>
void PencilMark::CheckGrid(int indexI, int indexJ)
{
	int index = _sudoku._boardDim * indexI + indexJ;
	int startI = (indexI / _sudoku._gridDim) * _sudoku._gridDim; // row index of the top-left cell of the grid
	int startJ = (indexJ / _sudoku._gridDim) * _sudoku._gridDim; // column index of the top-left cell of the grid
	for (int i = startI; i < startI + _sudoku._gridDim; i++)
	{
		for (int j = startJ; j < startJ + _sudoku._gridDim; j++)
		{
			int val = _sudoku._sudokuBoard[_sudoku._boardDim * i + j];
			if (val != 0)
				_pencilMarks[index][val - 1] = false;
		}
	}
}

/// <summary>
/// Attempts to mark a cell with a unique possible value based on its pencil marks.
/// </summary>
/// <param name="index">Index of the cell in the 1D array representation of the sudoku puzzle.</param>
/// <returns>The unique possible value to mark the cell, or 0 if multiple possibilities exist.</returns>
int PencilMark::TryToMark(int index)
{
	int val = 0;
	for (int i = 0; i < _sudoku._boardDim; i++)
	{
		if (_pencilMarks[index][i] == true)
		{
			if (val == 0)
				val = i + 1;
			else
				return 0;
		}
	}
	return val;
}

/// <summary>
/// Solves the sudoku puzzle using a pencil mark algorithm approach.
/// </summary>
/// <returns>The solved sudoku puzzle.</returns>
Sudoku PencilMark::Solve()
{
	int toSolve = _sudoku._boardDim * _sudoku._boardDim - CountFixedValues(); // the number of fields to fill

	while (toSolve > 0) // continue solving until all cells are filled
	{
		for (int i = 0; i < _sudoku._boardDim && toSolve > 0; i++)
		{
			for (int j = 0; j < _sudoku._boardDim && toSolve > 0; j++)
			{
				int index = _sudoku._boardDim * i + j;
				if (_sudoku._sudokuBoard[index] == 0)
				{
					// update pencil marks based on row, column, and grid
					CheckRow(i, index);
					CheckColumn(j, index);
					CheckGrid(i, j);

					_sudoku._sudokuBoard[index] = TryToMark(index);
					if (_sudoku._sudokuBoard[index] != 0)
						toSolve--;
				}
			}
		}
	}

	return _sudoku;
}