#include "sudokuCell.h"

#include <iostream>

using namespace std;

// Constructors
SudokuCell::SudokuCell()
{
  this->value = 0;
}

SudokuCell::SudokuCell(int value)
{
  this->value = SudokuCell::validate(value);
}

// Destructor
SudokuCell::~SudokuCell(){}

// Static functions
int SudokuCell::validate(int value)
{
  if (value < 0 || value > 9) return 0;
  return value;
}

// Public functions
int SudokuCell::getValue() { return this->value; }
void SudokuCell::setValue(int value)
{
  this->value = SudokuCell::validate(value);
}

void SudokuCell::print()
{
  cout << "Cell Value: " << this->value << endl;
}
