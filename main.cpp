#include <iostream>
#include <chrono>

#include "Sudoku.h"
#include "PencilMarkStrategy.h"

#include "BackTracingStrategy.h"
#include "EfficiencyTests.h"
#include "GeneticAlgorithmStrategy.h"
#include "GeneticAlgorithmBuilder.h"

void PrintDuration(std::chrono::microseconds duration) {
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
	duration -= minutes;
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
	duration -= seconds;
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	duration -= milliseconds;
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);

	std::cout << "Duration: "
		<< minutes.count() << ":"
		<< seconds.count() << ":"
		<< milliseconds.count() << "."
		<< microseconds.count() << std::endl;
}

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Sudoku sudoku = Sudoku(3, new int[81] {0, 8, 0, 0, 0, 0, 0, 9, 0,
		0, 0, 7, 5, 0, 2, 8, 0, 0,
		6, 0, 0, 8, 0, 7, 0, 0, 5,
		3, 7, 0, 0, 8, 0, 0, 5, 1,
		2, 0, 0, 0, 0, 0, 0, 0, 8,
		9, 5, 0, 0, 4, 0, 0, 3, 2,
		8, 0, 0, 1, 0, 4, 0, 0, 9,
		0, 0, 1, 9, 0, 3, 6, 0, 0,
		0, 4, 0, 0, 0, 0, 0, 2, 0, });

	Sudoku sudoku3 = Sudoku(3, new int[81] {0, 0, 6, 0, 0, 0, 0, 0, 0,
		0, 8, 0, 0, 5, 4, 2, 0, 0,
		0, 4, 0, 0, 9, 0, 0, 7, 0,
		0, 0, 7, 9, 0, 0, 3, 0, 0,
		0, 0, 0, 0, 8, 0, 4, 0, 0,
		6, 0, 0, 0, 0, 0, 1, 0, 0,
		2, 0, 3, 0, 0, 0, 0, 0, 1,
		0, 0, 0, 5, 0, 0, 0, 4, 0,
		0, 0, 8, 3, 0, 0, 5, 0, 2, });

	Sudoku sudoku2 = Sudoku(3, new int[81] {0, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 3, 0, 1, 0, 0, 0, 6,
		0, 4, 0, 0, 2, 0, 0, 3, 0,
		1, 0, 0, 0, 0, 3, 0, 0, 9,
		0, 0, 5, 0, 0, 0, 4, 0, 0,
		2, 0, 0, 6, 0, 0, 0, 0, 8,
		0, 9, 0, 0, 7, 0, 0, 4, 0,
		7, 0, 0, 0, 8, 0, 5, 0, 0,
		0, 0, 0, 0, 0, 0, 3, 0, 0, });

	//{0, 0, 0, 0, 0, 0, 0, 0, 0,
	//0, 0, 0, 0, 0, 0, 0, 0, 0,
	//0, 0, 0, 0, 0, 0, 0, 0, 0,
	//0, 0, 0, 0, 0, 0, 0, 0, 0,
	//0, 0, 0, 0, 0, 0, 0, 0, 0,
	//0, 0, 0, 0, 0, 0, 0, 0, 0,
	//0, 0, 0, 0, 0, 0, 0, 0, 0,
	//0, 0, 0, 0, 0, 0, 0, 0, 0,
	//0, 0, 0, 0, 0, 0, 0, 0, 0, }
		/*new int [81] {5, 3, 0, 0, 7, 0, 0, 0, 0,
						6, 0, 0, 1, 9, 5, 0, 0, 0,
						0, 9, 8, 0, 0, 0, 0, 6, 0,
						8, 0, 0, 0, 6, 0, 0, 0, 3,
						4, 0, 0, 8, 0, 3, 0, 0, 1,
						7, 0, 0, 0, 2, 0, 0, 0, 6,
						0, 6, 0, 0, 0, 0, 2, 8, 0,
						0, 0, 0, 0, 8, 0, 0, 7, 9});*/
	sudoku2.Print();

	/*PencilMark pencilMark(sudoku);
	Sudoku solved = pencilMark.Solve();

	solved.Print();*/

	/*std::cout<<Sudoku::WhichGrid(10);
	std::cout<<Sudoku::WhichGrid(14);
	std::cout<<Sudoku::WhichGrid(8);
	std::cout<<Sudoku::WhichGrid(57);*/

	//for (int i = 0; i < 9; i++)
	//{
	//	std::cout << sudoku2._IndexesByGrid[1].at(i) << std::endl;
	//}

	//BackTracing BackTracing(sudoku);
	//Sudoku solvedBack = BackTracing.Solve();
	//auto start = std::chrono::high_resolution_clock::now();

	//GeneticAlgorithmBuilder geneticbuilder = GeneticAlgorithmBuilder(sudoku);
	//// builderem wybierz strategie i inne parametry
	///*GeneticAlgorithm geneticAlgorithm = geneticbuilder.generationSize(10000).maxIter(10000).restartAfter(100).
	//	selectStrategy(GeneticAlgorithm::ParentSelectStrategy::Tournament).build();*/

	//GeneticAlgorithm geneticAlgorithm = geneticbuilder.generationSize(10000).maxIter(10000).restartAfter(100).
	//	selectStrategy(GeneticAlgorithm::ParentSelectStrategy::Roulette).build();
	//Sudoku solved = geneticAlgorithm.Solve();
	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	////std::cout <<"Duration: " << duration.count() << std::endl;
	//PrintDuration(duration);

	//solved.Print();
	//sudoku.Print();
	//solvedBack.Print();


	GeneticAlgorithmTester tester(sudoku2, "result.txt");
	tester.Config();
	tester.runTests();
}