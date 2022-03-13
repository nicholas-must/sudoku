#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <string>

class SudokuCell
{
 public:
  SudokuCell();
  SudokuCell(int digit);
  
  static int validate(int digit);

  int getDigit();
  void setDigit(int digit);
  
  void print();
  
 private:
  int digit; // 0 is unknown
  // TODO: candidates
};

#endif // SUDOKU_CELL_H
