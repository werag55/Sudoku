# Sudoku Solver Using Genetic Algorithm

Sudoku is a group student project carried out as part of the course "Introduction to artificial intelligence". The aim of the project was to use a genetic algorithm to solve classic 9x9 Sudoku puzzles[^1].

## Algorithm Pseudocode[^2]
```
generate initial population
repeat
    rank the solutions, and retain only the percentage specified by selection rate
    repeat
        randomly select two unused solutios from the population
        randomly choose a crossover points
        recombine the solutions to produce two new solutios
        apply the mutation operator to the solutions
    until a new population has been produced
until a solution is found or the maximum number of generations is reached
```

## Preprocessing

To reduce the size of the input problem, you can use the pencil mark algorithm. This algorithm cyclically iterates over each square on the board, remembering which values are impossible to insert in a given place (i.e. they are blocked by the occurrence of this value in a given row, column, or 3x3 subsquare). If only one value from 1-9 remains available, it is inserted onto the board.

## First Population

A heuristic initialization strategy was used to generate the initial population - empty squares on the Sudoku board are randomly filled, but the values within the 3x3 subsquares are kept unique, i.e. repetitions can only occur in columns or rows.

## Fitness Function

The suitability of the generated boards for a correct solution is assessed based on the number of repetitions that occur in rows and columns.

## Parent Selection

There are three strategies available for selecting individuals to pass on their genes to the next generation:

1. Elitism with random selection - based on the established parameters, a certain percentage of the best individuals are selected, and the missing part of the parents is filled with random boards.
2. Roulette selection - the probability of selecting a given individual as a parent is proportional to its fitness
3. Tournament selection - a certain number of individuals are randomly selected from the population, and then the best one from this group is selected as a parent

## Crossover

Analyzing the characteristics of the Sudoku solving problem and the structure of the board, we decided on a multi-point crossover, in which segments in the form of 3x3 subsquares from different parents are interwoven.

## Mutation

The swap mutation strategy was used. For a specified number of individuals, a 3x3 subsquare is drawn, in which two random values are swapped (of course, it is impossible to modify the values from the input Sudoku puzzle).

[^1]: David D., *Solving Sudoku puzzles with Genetic Algorithm*, https://nidragedd.github.io/sudoku-genetics/?fbclid=IwAR2XOArT7ngPySPg8Ap5fQHv6qROXT-M9azFdPvyH_0SBPlsUP2w9Ovswr8
[^2]: Dr. John M. Weiss, *Genetic Algorithms and Sudoku*, https://micsymposium.org/mics_2009_proceedings/mics2009_submission_66.pdf
