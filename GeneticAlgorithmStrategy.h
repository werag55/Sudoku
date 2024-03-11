#pragma once

#include "Sudoku.h"

class GeneticAlgorithm
{
	Sudoku _sudoku;

public:
	GeneticAlgorithm(const Sudoku& sudoku);
	Sudoku Solve();

private:
	void FillRandomGrid(int i, int j, Sudoku& sudoku);
	void FillRandom(Sudoku& sudoku);
	void GenerateFirstPopulation();
};