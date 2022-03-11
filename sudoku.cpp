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

void Sudoku::setRow(int row, int vals[9])
{
  for (int i = 0; i < 9; ++i)
    setCellValue(row, i + 1, vals[i]);
}

void Sudoku::setColumn(int col, int vals[9])
{
  for (int i = 0; i < 9; ++i)
    setCellValue(i + 1, col, vals[i]);
}

void Sudoku::setSquare(int x, int y, int vals[9])
{
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      setCellValue(1 + (3 * (y - 1)) + i,
		   1 + (3 * (x - 1)) + j,
		   vals[3 * i + j]);
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
