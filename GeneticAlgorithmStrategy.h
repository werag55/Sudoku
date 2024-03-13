#pragma once

#include "Sudoku.h"

class GeneticAlgorithm
{
	Sudoku _sudoku;
	Sudoku* _generation;
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
};