#pragma once

#include "GeneticAlgorithmStrategy.h"
class GeneticAlgorithmBuilder {
private:
    Sudoku _sudoku;
    int _generationSize = 10000;
    double _selectedPC = 0.25;
    double _randomPC = 0.25;
    int _children = 4;
    double _mutationPC = 0.25;
    int _maxIter = 5000;
    int _restartAfter = 30;
    GeneticAlgorithm::ParentSelectStrategy _selectStrategy = GeneticAlgorithm::ParentSelectStrategy::RankAndRandom;

public:

    GeneticAlgorithmBuilder(const Sudoku& sudoku) : _sudoku(sudoku) {}


    GeneticAlgorithmBuilder& generationSize(int size) {
        _generationSize = size;
        return *this;
    }

    GeneticAlgorithmBuilder& selectStrategy(GeneticAlgorithm::ParentSelectStrategy selectStrategy) {
        _selectStrategy = selectStrategy;
        return *this;
    }

    GeneticAlgorithmBuilder& selectedPC(double selectedPC) {
        _selectedPC = selectedPC;
        return *this;
    }


    GeneticAlgorithmBuilder& randomPC(double randomPC) {
        _randomPC = randomPC;
        return *this;
    }


    GeneticAlgorithmBuilder& children(int children) {
        _children = children;
        return *this;
    }


    GeneticAlgorithmBuilder& mutationPC(double mutationPC) {
        _mutationPC = mutationPC;
        return *this;
    }


    GeneticAlgorithmBuilder& maxIter(int maxIter) {
        _maxIter = maxIter;
        return *this;
    }


    GeneticAlgorithmBuilder& restartAfter(int restartAfter) {
        _restartAfter = restartAfter;
        return *this;
    }


    GeneticAlgorithm build() {

        return GeneticAlgorithm(_sudoku, _generationSize, _selectedPC, _randomPC, _children, _mutationPC, _maxIter, _restartAfter,_selectStrategy);
    }
};