#include "BackTracingStrategy.h"
#include <algorithm> 
/// <summary>
///  Constructor of Backtracking strategy
/// </summary>
/// <param name="sudoku">
/// puzzle to be solve
/// </param>
BackTracing::BackTracing(const Sudoku& sudoku)
{
	_sudoku = Sudoku(sudoku);

	// tablica haszujaca do sprawdzania czy sie powtarzaja elementy O(n)
	HashTable = new bool[sudoku._boardDim+1];
}



/// <summary>
/// Check for duplicates in row without 0
/// </summary>
/// <param name="i">
/// Row Number
/// </param>
/// <returns> Result true or false </returns>
bool BackTracing::CheckRow(int i)
{
	std::fill(HashTable, HashTable + _sudoku._boardDim + 1, false);

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

/// <summary>
/// Check for duplicates in column without 0
/// </summary>
/// <param name="i">
/// Column Number
/// </param>
/// <returns> Result true or false </returns>
bool BackTracing::CheckColumn(int j)
{
	std::fill(HashTable, HashTable + _sudoku._boardDim + 1, false);

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

/// <summary>
/// Check for duplicates in Grid without 0
/// </summary>
/// <param name="i">
/// Grid Number
/// </param>
/// <returns> Result true or false </returns>
bool BackTracing::CheckGrid(int indexI, int indexJ)
{
	std::fill(HashTable, HashTable + _sudoku._boardDim + 1, false);

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

/// <summary>
/// Check that board is still valid by checking conditions
/// </summary>
/// <returns></returns>
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


/// <summary>
/// Wraping Function
/// </summary>
/// <returns>
/// Solved Sudoku
/// </returns>
Sudoku BackTracing::Solve()
{
	bool result = Solving(0, 0);
	return _sudoku;

}
/// <summary>
/// Main Backtracking Function
/// </summary>
/// <param name="i"> row </param>
/// <param name="j"> column </param>
/// <returns> Solution Exists
/// </returns>
bool BackTracing::Solving(int i, int j)
{
	// row is 9 end, sudoku solved
	if (i == 9)
		return true;
	// column is 9, go to next row
	else if (j == 9)
		return Solving(i + 1, 0);
	// if there is already number go to next 
	else if (_sudoku._sudokuBoard[i * _sudoku._boardDim + j] != 0)
	{
		return Solving(i, j + 1);
	}
	else
	{
		// check all posibilities
		for (int iterator = 1; iterator < 10; iterator++)
		{
			// put there number
			_sudoku._sudokuBoard[i * _sudoku._boardDim + j] = iterator;

			// board is valid (preprocessing) and main function is true
			if (IsValid() && Solving(i, j + 1))
			{
				return true;
			}
			// undo if there is no solution
			_sudoku._sudokuBoard[i * _sudoku._boardDim + j] = 0;
		}
	}

	return false;
}