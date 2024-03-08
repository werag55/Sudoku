#pragma once

#include "PencilMarkStrategy.h"

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

void PencilMark::CheckRow(int i, int index)
{
	for (int j = 0; j < _sudoku._boardDim; j++)
	{
		int val = _sudoku._sudokuBoard[_sudoku._boardDim * i + j];
		if (val != 0)
			_pencilMarks[index][val - 1] = false;
	}
}


void PencilMark::CheckColumn(int j, int index)
{
	for (int i = 0; i < _sudoku._boardDim; i++)
	{
		int val = _sudoku._sudokuBoard[_sudoku._boardDim * i + j];
		if (val != 0)
			_pencilMarks[index][val - 1] = false;
	}
}

void PencilMark::CheckGrid(int indexI, int indexJ)
{
	int index = _sudoku._boardDim * indexI + indexJ;
	int startI = (indexI / _sudoku._gridDim) * _sudoku._gridDim;
	int startJ = (indexJ / _sudoku._gridDim) * _sudoku._gridDim;
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

Sudoku PencilMark::Solve()
{
	bool isSolved = false;

	while (!isSolved)
	{
		isSolved = true;
		for (int i = 0; i < _sudoku._boardDim; i++)
		{
			for (int j = 0; j < _sudoku._boardDim; j++)
			{
				int index = _sudoku._boardDim * i + j;
				if (_sudoku._sudokuBoard[index] == 0)
				{
					CheckRow(i, index);
					CheckColumn(j, index);
					CheckGrid(i, j);
					_sudoku._sudokuBoard[index] = TryToMark(index);
					if (isSolved && _sudoku._sudokuBoard[_sudoku._boardDim * i + j] == 0)
						isSolved = false;
				}
			}
		}

		_sudoku.Print();
	}

	return _sudoku;
}