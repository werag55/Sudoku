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

int GeneticAlgorithm::CountDuplicatesRowColumn(const Sudoku& sudoku, int i, int j)
{
	int duplicates = 0;
	bool* occuredRow = new bool[sudoku._boardDim];
	bool* occuredColumn = new bool[sudoku._boardDim];
	for (int ii = 0; ii < sudoku._boardDim; ii++)
	{
		occuredRow[ii] = false;
		occuredColumn[ii] = false;
	}

	for (int k = 0; k < sudoku._boardDim; k++)
	{
		// checking row
		int val = sudoku._sudokuBoard[sudoku._boardDim * i + k];
		if (!occuredRow[val - 1])
			occuredRow[val - 1] = true;
		else
			duplicates++;

		// checking column
		val = sudoku._sudokuBoard[sudoku._boardDim * k + j];
		if (!occuredColumn[val - 1])
			occuredColumn[val - 1] = true;
		else
			duplicates++;
	}

	return duplicates;
}

int GeneticAlgorithm::RateSolution(const Sudoku& sudoku)
{
	int score = 0;
	for (int k = 0; k < sudoku._boardDim; k++)
	{
		score += CountDuplicatesRowColumn(sudoku, k, k);
		std::cout << std::endl << score << std::endl;
	}
	return score;
}



Sudoku GeneticAlgorithm::Solve()
{
	GenerateFirstGeneration();
	_generation[0].Print();
	int score = RateSolution(_generation[0]);
	_generation[0].Print();
	std::cout << score << std::endl;
	return _sudoku;
}