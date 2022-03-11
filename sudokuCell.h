#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <string>

class SudokuCell
{
 public:
  SudokuCell();
  SudokuCell(int value);
  ~SudokuCell();
  
  static int validate(int value);

  int getValue();
  void setValue(int value);
  
  void print();
  
 private:
  int value; // 0 is unknown
};

#endif // SUDOKU_CELL_H
