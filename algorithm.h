#ifndef SUDOKU_ALGORITHM_H
#define SUDOKU_ALGORITHM_H

#include "sudokuDefs.h"

#include <set>

// Useful functions
SetSetInt powerSet(SetInt);
void combineSets(SetSetInt *sets, SetInt *outputSet);
void print_set(SetInt &set);
void print_set(SetSetInt &set);

#endif // SUDOKU_ALGORITHM_H
