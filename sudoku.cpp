#include "sudoku.h"
#include <iostream>

using namespace std;

// Constructor
Sudoku::Sudoku(){}

// Destructor
Sudoku::~Sudoku() {}

// Public methods
void Sudoku::setCellValue(int cellNumber, int cellValue)
{
  cells[cellNumber].setValue(cellValue);
}

void Sudoku::setCellValue(int row, int column, int cellValue)
{
  setCellValue((row - 1) * 9 + (column - 1), cellValue);
}

void Sudoku::print()
{
  for (int i = 0; i < 9; ++i)
  {
    if (0 == (i) % 3)
      cout << "-------------" << endl;
    
    // Print a row of numbers
    for (int j = 0; j < 9; ++j)
    {
      if (0 == (j) % 3)
	cout << "|";
      int offset = 9 * i + j;
      cout << cells[offset].getValue();
    }
    cout << "|" << endl;
  }
  cout << "-------------" << endl;
}
