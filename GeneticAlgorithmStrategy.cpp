#pragma once

#include <iostream>
#include "GeneticAlgorithmStrategy.h"
#include <cstdlib>
#include <ctime>
#include <set>

/// <summary>
/// Constructs a GeneticAlgorithm object.
/// </summary>
/// <param name="sudoku">The Sudoku puzzle to be solved.</param>
GeneticAlgorithm::GeneticAlgorithm(const Sudoku& sudoku)
{
	_sudoku = Sudoku(sudoku);
	_previousGenereation = new Sudoku[_generationSize];
	_generation = new Sudoku[_generationSize];
	_scores = new int[_generationSize];

	_notFixedIndexesByGrid = new std::vector<int>[sudoku._boardDim];
	FindNotFixedIndexes();
}

void GeneticAlgorithm::FindNotFixedIndexes()
{
	for (int i = 0; i < _sudoku._gridDim; i++) // iterate through row indexes of grids 
	{
		for (int j = 0; j < _sudoku._gridDim; j++) // iterate through column indexes of grids 
		{
			for (int ii = 0; ii < _sudoku._gridDim; ii++) // iterate through row indexes of the values in the grid
			{
				for (int jj = 0; jj < _sudoku._gridDim; jj++) // iterate through column indexes of the values in the grid
				{
					if (_sudoku._sudokuBoard[(i * _sudoku._gridDim + ii) * _sudoku._boardDim + (j * _sudoku._gridDim + jj)] == 0)
						_notFixedIndexesByGrid[i * _sudoku._gridDim + j].push_back
							((i * _sudoku._gridDim + ii) * _sudoku._boardDim + (j * _sudoku._gridDim + jj)); // index of the unfixed value
																											 // in sudoku board
				}
			}
		}
	}
}

/// <summary>
/// Fills a grid in the sudoku puzzle with random values, ensuring no duplicates.
/// </summary>
/// <param name="i">Row index of the grid.</param>
/// <param name="j">Column index of the grid.</param>
/// <param name="sudoku">The Sudoku puzzle to fill.</param>
void GeneticAlgorithm::FillRandomGrid(int i, int j, Sudoku& sudoku)
{

	bool* takenValues = new bool[sudoku._boardDim];
	for (int ii = 0; ii < sudoku._boardDim; ii++)
		takenValues[ii] = false;

	// fixed values
	for (int ii = i * sudoku._gridDim; ii < (i + 1) * sudoku._gridDim; ii++)
	{
		for (int jj = j * sudoku._gridDim; jj < (j + 1) * sudoku._gridDim; jj++)
		{
			int val = sudoku._sudokuBoard[_sudoku._boardDim * ii + jj];
			if (val != 0)
				takenValues[val - 1] = true;
		}
	}

	std::vector<int> freeValues; // stroe values that has not been placed in the grid being filled yet
	for (int ii = 1; ii <= sudoku._boardDim; ii++)
		if (!takenValues[ii - 1])
			freeValues.push_back(ii);

	for (int ii = i * sudoku._gridDim; ii < (i + 1) * sudoku._gridDim; ii++)
	{
		for (int jj = j * sudoku._gridDim; jj < (j + 1) * sudoku._gridDim; jj++)
		{
			// for each not filled field on the sudoku board, a value is drawn from among those that have not yet been used 
			if (sudoku._sudokuBoard[sudoku._boardDim * ii + jj] == 0) 
			{
				int randomIndex = rand() % freeValues.size();
				sudoku._sudokuBoard[sudoku._boardDim * ii + jj] = freeValues[randomIndex];
				freeValues.erase(freeValues.begin() + randomIndex);
			}
		}
	}
}

/// <summary>
/// Fills the entire sudoku puzzle with random values.
/// </summary>
/// <param name="sudoku">The sudoku puzzle to fill.</param>
void GeneticAlgorithm::FillRandom(Sudoku& sudoku)
{
	// each grid of the sudoku board is separately randomly filled 
	for (int i = 0; i < sudoku._boardDim / sudoku._gridDim; i++)
		for (int j = 0; j < sudoku._boardDim / sudoku._gridDim; j++)
			FillRandomGrid(i, j, sudoku);
}

/// <summary>
/// Generates the first population (generation) of sudoku puzzles with random values.
/// </summary>
void GeneticAlgorithm::GenerateFirstGeneration()
{
	srand(time(NULL));

	for (int i = 0; i < _generationSize; i++)
	{
		_generation[i] = Sudoku(_sudoku); // initialize each individual of the population by the orginal sudoku puzzle
		FillRandom(_generation[i]); // generate random solution
	}
}

/// <summary>
/// Counts the number of duplicate values in the specified row and column of the sudoku puzzle.
/// </summary>
/// <param name="sudoku">The sudoku puzzle to evaluate.</param>
/// <param name="i">Row index.</param>
/// <param name="j">Column index.</param>
/// <returns>The number of duplicate values found.</returns>
int GeneticAlgorithm::CountDuplicatesRowColumn(const Sudoku& sudoku, int i, int j)
{
	int duplicates = 0;

	// arrays to track the occurrence of values in the row and column.
	bool* occuredRow = new bool[sudoku._boardDim]; 
	bool* occuredColumn = new bool[sudoku._boardDim];
	for (int ii = 0; ii < sudoku._boardDim; ii++)
	{
		occuredRow[ii] = false;
		occuredColumn[ii] = false;
	}

	for (int k = 0; k < sudoku._boardDim; k++)
	{
		// check for duplicates in the row
		int val = sudoku._sudokuBoard[sudoku._boardDim * i + k];
		if (!occuredRow[val - 1])
			occuredRow[val - 1] = true; // mark the occurrence of the value
		else
			duplicates++; // increment duplicates count

		// check for duplicates in the column
		val = sudoku._sudokuBoard[sudoku._boardDim * k + j];
		if (!occuredColumn[val - 1])
			occuredColumn[val - 1] = true; // mark the occurrence of the value
		else
			duplicates++; // increment duplicates count
	}

	return duplicates;
}

/// <summary>
/// Rates the fitness of a solution based on the number of duplicates in rows and columns.
/// Note: There are no duplicates in grids, so it is not needed to check that.
/// </summary>
/// <param name="sudoku">The sudoku puzzle to rate.</param>
/// <returns>The fitness score of the solution.</returns>
int GeneticAlgorithm::RateSolution(const Sudoku& sudoku)
{
	int score = 0;
	for (int k = 0; k < sudoku._boardDim; k++)
		score += CountDuplicatesRowColumn(sudoku, k, k);
	return score;
}

/// <summary>
/// Evaluates the fitness of each sudoku puzzle in the current generation.
/// </summary>
void GeneticAlgorithm::Fitness()
{
	int minScore = INT_MAX; // the minimum score to find the best solution

	for (int k = 0; k < _generationSize; k++)
	{
		_scores[k] = RateSolution(_generation[k]);
		if (_scores[k] < minScore)
		{
			minScore = _scores[k];
			_bestSudokuIndex = k;
		}
	}

	if (_scores[_bestSudokuIndex] == _previousBestScore)
		_bestScoreNotChangedSince++; // update the number for subsequent generations without a change in the best score
	else
		_bestScoreNotChangedSince == 0;

	_previousBestScore = _scores[_bestSudokuIndex];
}

/// <summary>
/// Finds the maximum score among the selected percentage of best solutions in the current generation.
/// </summary>
/// <returns>The maximum best score found.</returns>
int GeneticAlgorithm::FindMaxBestScore()
{
	std::multiset<int, std::greater<int>> bestScores; // store best scores in descending order

	for (int k = 0; k < _selectedPC * _generationSize; k++) // fill the bestScores with first values
		bestScores.insert(_scores[k]);

	// iterate through the rest of the solutions to find better scores than the ones already in the set
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

/// <summary>
/// Determines the indexes of parent sudoku puzzles based on their scores and random selection.
/// </summary>
/// <param name="score">The score threshold for selecting best parents.</param>
void GeneticAlgorithm::FindParentsIndexes(int score)
{

	_parentsIndexes.clear(); // clear the current parent indexes
	std::vector<int> _notBestIndexes; // store indexes of non-best parents (to draw from them)

	for (int k = 0; k < _generationSize; k++)
	{
		if (_scores[k] <= score && _parentsIndexes.size() < _selectedPC * _generationSize)
			_parentsIndexes.push_back(k); // parent sudoku puzzles selected by their best scores
		else
			_notBestIndexes.push_back(k);
	}

	for (int k = 0; k < _randomPC * _generationSize; k++)
	{
		int randomIndex = rand() % _notBestIndexes.size();
		_parentsIndexes.push_back(_notBestIndexes[randomIndex]); // parent sudoku puzzles randomly selected
		_notBestIndexes.erase(_notBestIndexes.begin() + randomIndex);
	}

}

/// <summary>
/// Creates a child cudoku puzzle by combining characteristics of two parent puzzles.
/// </summary>
/// <param name="father">The cudoku puzzle representing the father.</param>
/// <param name="mother">The cudoku puzzle representing the mother.</param>
/// <returns>The child sudoku puzzle generated from the parents.</returns>
Sudoku GeneticAlgorithm::CreateChild(const Sudoku& father, const Sudoku& mother)
{
	
	int fromMother = rand() % (father._boardDim - 1) + 1; // determine the number of grid segments to inherit from the mother

	std::vector<std::tuple<int, int>> freeIndexes; // store the grid indexes available for inheritance
	for (int i = 0; i < father._gridDim; i++)
		for (int j = 0; j < father._gridDim; j++)
			freeIndexes.push_back(std::make_tuple(i, j));

	Sudoku child(father); // create a child sudoku puzzle initialized with the father's characteristics

	// inherit grid segments from the mother based on the determined number
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

/// <summary>
/// Generates children sudoku puzzles from selected parent pair.
/// </summary>
/// <param name="father">The cudoku puzzle representing the father.</param>
/// <param name="mother">The cudoku puzzle representing the mother.</param>
/// <param name="startIndex">The starting index in the _generation array to place children.</param>
void GeneticAlgorithm::CreateChildren(const Sudoku& father, const Sudoku& mother, int startIndex)
{
	for (int k = 0; k < _children; k++)
		_generation[k + startIndex] = CreateChild(father, mother);
}

/// <summary>
/// Generates the next generation of sudoku puzzles using genetic algorithm operations such as selection and crossover.
/// </summary>
void GeneticAlgorithm::GenerateGeneration()
{
	// save current generation as _previousGeneration
	_previousGenereation = new Sudoku[_generationSize];
	for (int k = 0; k < _generationSize; k++)
		_previousGenereation[k] = Sudoku(_generation[k]);

	srand(time(NULL));
	FindParentsIndexes(FindMaxBestScore());

	// perform crossover to generate children for the next generation
	for (int k = 0; k < _generationSize; k += _children)
	{
		// select father and mother indexes randomly from the parent indexes
		int randomIndex = rand() % _parentsIndexes.size();
		int fatherIndex = _parentsIndexes[randomIndex];
		_parentsIndexes.erase(_parentsIndexes.begin() + randomIndex);

		randomIndex = rand() % _parentsIndexes.size();
		int motherIndex = _parentsIndexes[randomIndex];
		_parentsIndexes.erase(_parentsIndexes.begin() + randomIndex);

		// create children from selected parents and place them in the _generation array
		CreateChildren(_previousGenereation[fatherIndex], _previousGenereation[motherIndex], k);
	}
}

/// <summary>
/// Swaps values at two specified indexes within a sudoku puzzle.
/// </summary>
/// <param name="sudoku">The sudoku puzzle to perform the swap operation.</param>
/// <param name="index1">The index of the first value to swap.</param>
/// <param name="index2">The index of the second value to swap.</param>
void GeneticAlgorithm::SwapValues(Sudoku& sudoku, int index1, int index2)
{
	int temp = sudoku._sudokuBoard[index1];
	sudoku._sudokuBoard[index1] = sudoku._sudokuBoard[index2];
	sudoku._sudokuBoard[index2] = temp;
}

/// <summary>
/// Applies mutation to a sudoku puzzle by randomly swapping values within a grid.
/// </summary>
/// <param name="sudoku">The sudoku puzzle to mutate.</param>
void GeneticAlgorithm::MutateSudoku(Sudoku& sudoku)
{
	int gridIndex = rand() % sudoku._boardDim;
	
	if (_notFixedIndexesByGrid[gridIndex].size() > 1)
	{
		int randomIndex1 = rand() % _notFixedIndexesByGrid[gridIndex].size();
		int randomIndex2 = rand() % (_notFixedIndexesByGrid[gridIndex].size() - 1);

		if (randomIndex2 >= randomIndex1)
			randomIndex2++;

		SwapValues(sudoku, _notFixedIndexesByGrid[gridIndex][randomIndex1], _notFixedIndexesByGrid[gridIndex][randomIndex2]);
	}
}

/// <summary>
/// Mutates a part of the population of sudoku puzzles.
/// </summary>
void GeneticAlgorithm::MutatePopulation()
{
	std::vector<int> _notMutatedIndexes; // indexes (int the _generation array)of the sudoku 
										 // puzzles that have not been mutated yet 
	for (int k = 0; k < _generationSize; k++)
		_notMutatedIndexes.push_back(k);

	srand(time(NULL));

	for (int k = 0; k < _mutationPC * _generationSize; k++)
	{
		int randomIndex = rand() % _notMutatedIndexes.size();
		MutateSudoku(_generation[_notMutatedIndexes[randomIndex]]);
		_notMutatedIndexes.erase(_notMutatedIndexes.begin() + randomIndex);
	}
}

/// <summary>
/// Solves the Sudoku puzzle using a genetic algorithm approach.
/// </summary>
/// <returns>The solved Sudoku puzzle.</returns>
Sudoku GeneticAlgorithm::Solve()
{
	GenerateFirstGeneration();

	int k;
	for (k = 0; k < _maxIter; k++)
	{
		if (_bestScoreNotChangedSince == _restartAfter)
		{
			GenerateFirstGeneration();
			_bestScoreNotChangedSince = 0;
			_restartCount++;
			std::cout << _restartCount <<". RESTART (stucked at best score : " <<_scores[_bestSudokuIndex] <<")\n";
		}

		Fitness();
		if (_scores[_bestSudokuIndex] == 0) // sudoku solved
			break;

		GenerateGeneration();

		if (!_evolutionary)
			MutatePopulation();
	}

	std::cout << "Solved after " << _restartCount << " restarts (" << _restartCount * _restartAfter << " iterations) and "
		<< k % _restartAfter << " iterations.\n";
	return _generation[_bestSudokuIndex];
}