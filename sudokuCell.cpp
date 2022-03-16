#include "sudokuCell.h"

#include "sudokuDefs.h"

#include <iostream>

using namespace std;

// Constructors
SudokuCell::SudokuCell()
{
  this->digit = 0;
}

SudokuCell::SudokuCell(int digit)
{
  setDigit(digit);
}

// Static functions
int SudokuCell::validate(int digit)
{
  if (digit < 0 || digit > 9) return 0;
  return digit;
}

// Public functions
int SudokuCell::getDigit() { return this->digit; }
void SudokuCell::setDigit(int digit)
{
  this->digit = SudokuCell::validate(digit);
}

void SudokuCell::initiateCandidates()
{
  // No need to compute candidates for known cell
  if (digit != 0) return;

  if (candidates.empty())
  {
    for (int i = 1; i <= 9; ++i)
      candidates.insert(i);
  }
}

void SudokuCell::print()
{
  cout << "Cell Digit: " << this->digit << endl;
}
