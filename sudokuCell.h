#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <string>

class SudokuRow;
class SudokuColumn;
class SudokuSquare;

class SudokuCell
{
 public:
  SudokuCell();
  SudokuCell(int digit);
  
  static int validate(int digit);

  int getDigit();
  void setDigit(int digit);
  
  void print();

  SudokuRow *row;
  SudokuColumn *column;
  SudokuSquare *square;
  
 private:
  int digit; // 0 is unknown
  // TODO: candidates
};

#endif // SUDOKU_CELL_H
