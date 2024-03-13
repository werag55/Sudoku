#pragma once

#include <iostream>
#include "GeneticAlgorithmStrategy.h"
#include <cstdlib>
#include <ctime>
#include "vector"

GeneticAlgorithm::GeneticAlgorithm(const Sudoku& sudoku)
{
	_sudoku = Sudoku(sudoku);
	_generation = new Sudoku[_generationSize];
}

void GeneticAlgorithm::FillRandomGrid(int i, int j, Sudoku& sudoku)
{

	bool* takenValues = new bool[sudoku._boardDim];
	for (int ii = 0; ii < sudoku._boardDim; ii++)
		takenValues[ii] = false;

	//fixed values
	for (int ii = i * sudoku._gridDim; ii < (i + 1) * sudoku._gridDim; ii++)
	{
		for (int jj = j * sudoku._gridDim; jj < (j + 1) * sudoku._gridDim; jj++)
		{
			int val = sudoku._sudokuBoard[_sudoku._boardDim * ii + jj];
			if (val != 0)
				takenValues[val - 1] = true;
		}
	}

	std::vector<int> freeValues;
	for (int ii = 1; ii <= sudoku._boardDim; ii++)
		if (!takenValues[ii - 1])
			freeValues.push_back(ii);

	for (int ii = i * sudoku._gridDim; ii < (i + 1) * sudoku._gridDim; ii++)
	{
		for (int jj = j * sudoku._gridDim; jj < (j + 1) * sudoku._gridDim; jj++)
		{
			if (sudoku._sudokuBoard[sudoku._boardDim * ii + jj] == 0)
			{
				int randomIndex = rand() % freeValues.size();
				sudoku._sudokuBoard[sudoku._boardDim * ii + jj] = freeValues[randomIndex];
				freeValues.erase(freeValues.begin() + randomIndex);
			}
		}
	}
}

void GeneticAlgorithm::FillRandom(Sudoku& sudoku)
{
	for (int i = 0; i < sudoku._boardDim / sudoku._gridDim; i++)
		for (int j = 0; j < sudoku._boardDim / sudoku._gridDim; j++)
			FillRandomGrid(i, j, sudoku);
}

void GeneticAlgorithm::GenerateFirstGeneration()
{
	srand(time(NULL));

	for (int i = 0; i < _generationSize; i++)
	{
		_generation[i] = Sudoku(_sudoku);
		FillRandom(_generation[i]);
	}
}

Sudoku GeneticAlgorithm::Solve()
{
	GenerateFirstGeneration();
	return _sudoku;
}