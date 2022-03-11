#ifndef SUDOKU_H
#define SUDOKU_H

#include "sudokuCell.h"

class Sudoku
{
 public:
  Sudoku();
  ~Sudoku();
  
  void setCellValue(int cellNumber, int cellValue);
  void setCellValue(int row, int column, int cellValue);
  void setRow(int row, int vals[9]);
  void setColumn(int col, int vals[9]);
  void setSquare(int x, int y, int vals[9]);

  int getCellValue(int cellNumber);
  int getCellValue(int row, int column);
  
  void print();

  bool validate();
  bool solve();
  
 private:
  SudokuCell cells[81];
  int buf9[9]; // re-usable
};

#endif // SUDOKU_H
