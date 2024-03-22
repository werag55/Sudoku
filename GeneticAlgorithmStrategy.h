#pragma once

#include "Sudoku.h"
#include "vector"
#include <tuple>
#include <algorithm>

class GeneticAlgorithm
{
public:
	enum class ParentSelectStrategy {
		RankAndRandom,
		Tournament,
		Roulette,
	};

	GeneticAlgorithm(const Sudoku& sudoku, int generationSize, double selectedPC, double randomPC, int children, double mutationPC, int maxIter, int restartAfter, ParentSelectStrategy selectStrategy);
	Sudoku Solve();

private:

	Sudoku _sudoku;								// the original sudoku puzzle
	Sudoku* _previousGenereation;				// the previous generation of sudoku puzzles
	Sudoku* _generation;						// the current generation of sudoku puzzles
	std::vector<int> _parentsIndexes;			// the indexes of parent sudoku puzzles in _generation array
	std::vector<int>* _notFixedIndexesByGrid;	// the indexes of unfixed cells of the orginal sudoku puzzle by grids
	int* _scores;								// the fitness scores of sudoku puzzles in the current generation
	// (at the i-th index in _scores there is the score for the sudoku puzzl

	double* _propabilityRoulette;			    // _scores transform into propability of choosing
	ParentSelectStrategy _selectStrategy;
	double* _comulatedPropability;		        // comulated propability for roulette

	bool _evolutionary = false;					// indicates whether the approach should be an evolutionary algorithm
	// (i.e. a genetic algorithm without mutations)
	int _generationSize = 10000;			    // the size of each generation
	double _selectedPC = 0.25;					// the percentage of the best solutions to be selected for crossover
	double _randomPC = 0.25;					// the percentage of randomly selected solutions for crossover
	int _children = 4;							// the number of children to be generated from each parent pair
	double _mutationPC = 0.25;					// the percentage of the population to be mutated
	int _maxIter = 5000;						// the maximum number of iterations for the genetic algorithm
	int _restartAfter = 30;						// the number of generations after which the algorithm restarts
	// if the best score remains unchanged
	int _restartCount = 0;						// the counter for restaring the algorithm
	int _previousBestScore = 0;					// the best score from the previous iteration
	int _bestSudokuIndex = 0;					// the index of the best solution in the _generation
	int _bestScoreNotChangedSince = 0;			// the number of iterations since the best score remained unchanged

	void FindNotFixedIndexes();
	void FillRandomGrid(int i, int j, Sudoku& sudoku);
	void FillRandom(Sudoku& sudoku);
	void GenerateFirstGeneration();
	int CountDuplicatesRowColumn(const Sudoku& sudoku, int i, int j);
	int RateSolution(const Sudoku& sudoku);
	void Fitness();
	int FindMaxBestScore();
	void FindParentsIndexes(int score);
	Sudoku CreateChild(const Sudoku& father, const Sudoku& mother);
	void CreateChildren(const Sudoku& father, const Sudoku& mother, int startIndex);
	void FindParentsIndexesRoulette();
	void GenerateGeneration();
	void SwapValues(Sudoku& sudoku, int index1, int index2);
	void MutateSudoku(Sudoku& sudoku);
	void MutatePopulation();
	void FindParentsIndexesTournament(int k);
};