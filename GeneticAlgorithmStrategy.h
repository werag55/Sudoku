#pragma once

#include "Sudoku.h"
#include "vector"

class GeneticAlgorithm
{
	Sudoku _sudoku;
	Sudoku* _previousGenereation;
	Sudoku* _generation;
	std::vector<int> _parentsIndexes;
	int* _scores;
	int _generationSize = 16;
	double _selectedPC = 0.25;
	double _randomPC = 0.25;
	int _children = 4;
	int _maxIter = 500;
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
	void MutateSudoku(int index);
	void MutatePopulation();
	void GenerateGeneration();
};