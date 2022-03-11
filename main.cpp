#include <iostream>

#include "sudoku.h"

using namespace std;

int main()
{
  cout << "Hello, world!" << endl;

  // game driver
  Sudoku sudoku;
  sudoku.setCellValue(0, 1);
  sudoku.setCellValue(80, 2);
  sudoku.setCellValue(5, 5, 3);
  sudoku.print();

  //cell driver
  SudokuCell cellKnown(9);
  SudokuCell cellUnknown;
  SudokuCell invalidCell(10);
  cellKnown.print();
  cellUnknown.print();
  invalidCell.print();
  //cout << "The known value is " << cellKnown
  

  cout << "End" << endl;
  
  return 0;
}
