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

void PencilMark::CheckRow(int i, int j)
{

}


void PencilMark::CheckColumn(int j)
{

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
				if (_sudoku._sudokuBoard[_sudoku._boardDim * i + j] == 0)
				{

					if (isSolved && _sudoku._sudokuBoard[_sudoku._boardDim * i + j] == 0)
						isSolved = false;
				}
			}
		}
	}
}