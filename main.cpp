#include <iostream>

#include "Sudoku.h"
#include "PencilMarkStrategy.h"

int main(int argc, char* argv[])
{
	Sudoku sudoku = Sudoku(3, new int [81] {5, 3, 0, 0, 7, 0, 0, 0, 0,
											6, 0, 0, 1, 9, 5, 0, 0, 0,
											0, 9, 8, 0, 0, 0, 0, 6, 0,
											8, 0, 0, 0, 6, 0, 0, 0, 3,
											4, 0, 0, 8, 0, 3, 0, 0, 1,
											7, 0, 0, 0, 2, 0, 0, 0, 6,
											0, 6, 0, 0, 0, 0, 2, 8, 0,
											0, 0, 0, 0, 8, 0, 0, 7, 9});
	sudoku.Print();

	PencilMark pencilMark(sudoku);
	Sudoku solved = pencilMark.Solve();
	solved.Print();
}