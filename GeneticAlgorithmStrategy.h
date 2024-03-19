#pragma once

#include "Sudoku.h"
#include "vector"
#include <tuple> 

class GeneticAlgorithm
{
	Sudoku _sudoku;
	Sudoku* _previousGenereation;
	Sudoku* _generation;
	std::vector<int> _parentsIndexes;
	std::vector<int>* _notFixedIndexesByGrid;
	int* _scores;
	int _generationSize = 5000;
	double _selectedPC = 0.25;
	double _randomPC = 0.25;
	int _children = 4;
	double _mutationPC = 0.25;
	int _maxIter = 650;
	int _restartAfter = 30;
	int _previousBestScore = 0;
	int _bestSudokuIndex = 0;
	int _bestScoreNotChangedSince = 0;
public:
	GeneticAlgorithm(const Sudoku& sudoku);
	Sudoku Solve();

private:
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
	void GenerateGeneration();
	void SwapValues(Sudoku& sudoku, int index1, int index2);
	void MutateSudoku(Sudoku& sudoku);
	void MutatePopulation();
};