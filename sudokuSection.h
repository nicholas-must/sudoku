#ifndef SUDOKU_SECTION_H
#define SUDOKU_SECTION_H

#include "sudokuDefs.h"
#include "sudokuCell.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// TODO: override []
struct Set9
{
  SudokuCell *set[9];
};

// Base class
class SudokuSection
{
 public:
  SudokuSection();
  ~SudokuSection();

  virtual string getName(); // TODO: Find a way to make pure virtual
  
  Set9 getCells(); // TODO: is this needed?
  SudokuCell *getCell(int index);
  void setCell(int index, SudokuCell *cell);
  void print();

  bool forAll(ScanFunction func, ScanContext *context);

 private:
  Set9 cells;
};

// Derived classes
class SudokuRow : public SudokuSection
{
 public:
  string getName();
};

class SudokuColumn : public SudokuSection
{
 public:
  string getName();
};

class SudokuSquare : public SudokuSection
{
 public:
  string getName();
};
#endif // SUDOKU_SECTION_H
