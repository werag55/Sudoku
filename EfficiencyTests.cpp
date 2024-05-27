#include "TestConfig.h"
#include "EfficiencyTests.h"
#include "GeneticAlgorithmBuilder.h"
#include <fstream>
#include <iostream>
#include <chrono>

void GeneticAlgorithmTester::runTests() {
	std::ofstream outFile(outputFileName);
	if (!outFile.is_open()) {
		std::cerr << "Failed to open " << outputFileName << std::endl;
		return;
	}

	outFile << "GenerationSize,MaxIter,RestartAfter,SelectStrategy,Duration(us),Iterations,bestScore,isSolved\n";

	for (const auto& config : configs) {
		auto start = std::chrono::high_resolution_clock::now();

		GeneticAlgorithmBuilder builder(sudoku);
		GeneticAlgorithm geneticAlgorithm = builder
			.generationSize(config.generationSize)
			.maxIter(config.maxIter)
			.restartAfter(config.restartAfter)
			.selectStrategy(config.selectStrategy)
			.build();

		geneticAlgorithm.Solve();
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

		outFile << config.generationSize << ","
			<< config.maxIter << ","
			<< config.restartAfter << ","
			<< static_cast<int>(config.selectStrategy) << ","
			<< duration << ","
			<< geneticAlgorithm._iterationsnumber << ","
			<< geneticAlgorithm._bestScore << ","
			<< geneticAlgorithm._solved << "\n";
	}

	outFile.close();
}

void GeneticAlgorithmTester::Config() {
	configs.clear();

	int maxIter = 500;
	int restartAfter = 100;
	GeneticAlgorithm::ParentSelectStrategy selectStrategy = GeneticAlgorithm::ParentSelectStrategy::Roulette;

	// memory leaki idk
	for (int generationSize = 6000; generationSize <= 10000; generationSize += 1000) {
		TestConfig config;
		config.generationSize = generationSize;
		config.maxIter = maxIter;
		config.restartAfter = restartAfter;
		config.selectStrategy = selectStrategy;

		configs.push_back(config);
		config.selectStrategy = GeneticAlgorithm::ParentSelectStrategy::Tournament;
		configs.push_back(config);

		config.selectStrategy = GeneticAlgorithm::ParentSelectStrategy::RankAndRandom;
		configs.push_back(config);
	}
}