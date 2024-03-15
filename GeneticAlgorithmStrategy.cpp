#pragma once

#include <iostream>
#include "GeneticAlgorithmStrategy.h"
#include <cstdlib>
#include <ctime>
#include <set>
#include <tuple> 

GeneticAlgorithm::GeneticAlgorithm(const Sudoku& sudoku)
{
	_sudoku = Sudoku(sudoku);
	_generation = new Sudoku[_generationSize];
	_scores = new int[_generationSize];
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
		score += CountDuplicatesRowColumn(sudoku, k, k);
	return score;
}

void GeneticAlgorithm::Fitness()
{
	for (int k = 0; k < _generationSize; k++)
		_scores[k] = RateSolution(_generation[k]);
}

int GeneticAlgorithm::FindMaxBestScore()
{
	std::multiset<int, std::greater<int>> bestScores;

	for (int k = 0; k < _selectedPC * _generationSize; k++)
		bestScores.insert(_scores[k]);

	for (int k = (int)(_selectedPC * _generationSize); k < _generationSize; k++)
	{
		if (_scores[k] < *bestScores.begin())
		{
			bestScores.erase(bestScores.begin());
			bestScores.insert(_scores[k]);
		}
	}

	return *bestScores.begin();
}

void GeneticAlgorithm::FindParentsIndexes(int score)
{
	_parentsIndexes.clear();
	std::vector<int> _notBestIndexes;

	for (int k = 0; k < _generationSize; k++)
	{
		if (_scores[k] <= score && _parentsIndexes.size() < _selectedPC * _generationSize)
			_parentsIndexes.push_back(k);
		else
			_notBestIndexes.push_back(k);
	}

	for (int k = 0; k < _randomPC * _generationSize; k++)
	{
		int randomIndex = rand() % _notBestIndexes.size();
		_parentsIndexes.push_back(_notBestIndexes[randomIndex]);
		_notBestIndexes.erase(_notBestIndexes.begin() + randomIndex);
	}

}

Sudoku GeneticAlgorithm::CreateChild(const Sudoku& father, const Sudoku& mother)
{
	int fromMother = rand() % (father._boardDim - 1) + 1;

	std::vector<std::tuple<int, int>> freeIndexes;
	for (int i = 0; i < father._gridDim; i++)
		for (int j = 0; j < father._gridDim; j++)
			freeIndexes.push_back(std::make_tuple(i, j));

	Sudoku child(father);

	for (int k = 0; k < fromMother; k++)
	{
		int randomIndex = rand() % freeIndexes.size();
		std::tuple<int, int> gridIndexes = freeIndexes[randomIndex];
		freeIndexes.erase(freeIndexes.begin() + randomIndex);

		int i = std::get<0>(gridIndexes);
		int j = std::get<1>(gridIndexes);

		for (int ii = i * child._gridDim; ii < (i + 1) * child._gridDim; ii++)
			for (int jj = j * child._gridDim; jj < (j + 1) * child._gridDim; jj++)
				child._sudokuBoard[child._boardDim * ii + jj] = mother._sudokuBoard[child._boardDim * ii + jj];
	}

	return child;
}

void GeneticAlgorithm::CreateChildren(const Sudoku& father, const Sudoku& mother, int startIndex)
{
	for (int k = 0; k < _children; k++)
	{
		_generation[k + startIndex] = CreateChild(father, mother);
		_generation[k + startIndex].Print();
	}
}

void GeneticAlgorithm::GenerateGeneration()
{
	_previousGenereation = new Sudoku[_generationSize];
	for (int k = 0; k < _generationSize; k++)
		_previousGenereation[k] = Sudoku(_generation[k]);

	srand(time(NULL));
	FindParentsIndexes(FindMaxBestScore());

	for (int k = 0; k < _generationSize; k += _children)
	{
		int randomIndex = rand() % _parentsIndexes.size();
		int fatherIndex = _parentsIndexes[randomIndex];
		_parentsIndexes.erase(_parentsIndexes.begin() + randomIndex);

		randomIndex = rand() % _parentsIndexes.size();
		int motherIndex = _parentsIndexes[randomIndex];
		_parentsIndexes.erase(_parentsIndexes.begin() + randomIndex);

		CreateChildren(_previousGenereation[fatherIndex], _previousGenereation[motherIndex], k);
	}

}

Sudoku GeneticAlgorithm::Solve()
{
	GenerateFirstGeneration();

	for (int k = 0; k < _maxIter; k++)
	{
		Fitness();
		GenerateGeneration();
	}

	return _sudoku;
}