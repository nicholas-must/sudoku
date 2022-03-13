#include "sudokuSection.h"

#include <iostream>
using namespace std;

// Sudoku Section

SudokuSection::SudokuSection(){}
SudokuSection::~SudokuSection(){}

// TODO: Find a way to get rid of this
string SudokuSection::getName()
{
  return "<section>";
}

Set9 SudokuSection::getCells()
{
  return cells;
}

SudokuCell* SudokuSection::getCell(int index)
{
  return cells.set[index];
}

void SudokuSection::setCell(int index, SudokuCell *cell)
{
  cells.set[index] = cell;
}

void SudokuSection::print()
{
  cout << getName() << ": ";
  for (int i = 0; i < 9; ++i)
  {
    cout << cells.set[i]->getDigit() <<
      (i == 8 ? "":",");
  }
  cout << endl;
}

bool SudokuSection::forAll(ScanFunction func,
			   ScanContext *context)
{
  context->section = this;
  for (int i = 0; i < 9; ++i)
  {
    context->minor = i + 1;
    context->cell = getCell(i);
    int ret = func(context);
    if (ret) return ret;
  }
  return 0; // continue
}

// Virtual overrides
// TODO: could be more re-usable
string SudokuRow::getName() { return "Row"; }
string SudokuColumn::getName() { return "Column"; }
string SudokuSquare::getName() { return "Square"; }
