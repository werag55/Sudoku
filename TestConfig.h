#pragma once

#include "GeneticAlgorithmStrategy.h" 

struct TestConfig {
    int generationSize;
    int maxIter;
    int restartAfter;
    GeneticAlgorithm::ParentSelectStrategy selectStrategy;
};
