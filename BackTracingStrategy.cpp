#include "BackTracingStrategy.h"
#include <algorithm> 

BackTracing::BackTracing(const Sudoku& sudoku)
{
	_sudoku = Sudoku(sudoku);

	// tablica haszujaca do sprawdzania czy sie powtarzaja elementy O(n)
	HashTable = new bool[10];
}




bool BackTracing::CheckRow(int i)
{
	std::fill(HashTable, HashTable + 10, false);

	for (int j = 0; j < _sudoku._boardDim; j++)
	{
		int val = _sudoku._sudokuBoard[_sudoku._boardDim * i + j];
		if (val != 0)
		{
			if (HashTable[val] == true)
			{
				return false;
			}
			HashTable[val] = true;

		}
			
	}
	return true;
}

bool BackTracing::CheckColumn(int j)
{
	std::fill(HashTable, HashTable + 10, false);

	for (int i = 0; i < _sudoku._boardDim; i++)
	{
		int val = _sudoku._sudokuBoard[_sudoku._boardDim * i + j];
		if (val != 0)
		{
			if (HashTable[val] == true)
			{
				return false;
			}
			HashTable[val] = true;

		}
	}
	return true;
}

bool BackTracing::CheckGrid(int indexI, int indexJ)
{
	std::fill(HashTable, HashTable + 10, false);

	int index = _sudoku._boardDim * indexI + indexJ;
	int startI = (indexI / _sudoku._gridDim) * _sudoku._gridDim;
	int startJ = (indexJ / _sudoku._gridDim) * _sudoku._gridDim;
	for (int i = startI; i < startI + _sudoku._gridDim; i++)
	{
		for (int j = startJ; j < startJ + _sudoku._gridDim; j++)
		{
			int val = _sudoku._sudokuBoard[_sudoku._boardDim * i + j];
			if (val != 0)
			{
				if (HashTable[val] == true)
				{
					return false;
				}
				HashTable[val] = true;

			}
		}
	}

	return true;
}

bool BackTracing::IsValid()
{
	for (int i = 0; i < _sudoku._boardDim; i++)
	{
		//popraw na board dim pozniej
		if (!CheckRow(i) || !CheckColumn(i) || !CheckGrid(i % 3 * 3, i / 3 * 3))
		{
			return false;
		}
	}
	return true;
}

Sudoku BackTracing::Solve()
{
	bool result = Solving(0, 0);
	return _sudoku;

}

bool BackTracing::Solving(int i, int j)
{
	if (i == 9)
		return true;

	else if (j == 9)
		return Solving(i + 1, 0);

	else if (_sudoku._sudokuBoard[i * _sudoku._boardDim + j] != 0)
	{
		return Solving(i, j + 1);
	}
	else
	{
		for (int iterator = 1; iterator < 10; iterator++)
		{
			_sudoku._sudokuBoard[i * _sudoku._boardDim + j] = iterator;
			if (IsValid() && Solving(i, j + 1))
			{
				return true;
			}

			_sudoku._sudokuBoard[i * _sudoku._boardDim + j] = 0;
		}
	}

	return false;
}