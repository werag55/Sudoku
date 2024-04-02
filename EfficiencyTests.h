#pragma once

#include <string>
#include <vector>
#include "TestConfig.h" // Zaimportuj strukturê TestConfig
#include "Sudoku.h" // Za³ó¿my, ¿e istnieje klasa Sudoku

class GeneticAlgorithmTester {
private:
    Sudoku sudoku;
    std::vector<TestConfig> configs;
    std::string outputFileName;

public:
    GeneticAlgorithmTester(Sudoku sudoku, std::string outputFileName) :sudoku(sudoku), outputFileName(outputFileName) {}
    GeneticAlgorithmTester() = default;
    void runTests();

    void Config();
};
