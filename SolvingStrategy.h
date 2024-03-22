#pragma once
#include "Sudoku.h"

class SolvingStrategy
{
protected:
	Sudoku _sudoku;

public:
	virtual void Solve();
};