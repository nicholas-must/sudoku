#ifndef SUDOKU_H
#define SUDOKU_H

#include "sudokuCell.h"
#include "sudokuSection.h"

// Try this before moving to another file
int validateBoard(ScanContext *context);
int soleCandidate(ScanContext *context);

class Sudoku
{
 public:
  Sudoku();

  int loadFile(string filename);
  int saveFile(string filename);
  
  void setCellDigit(int cellIndex, int cellValue);
  void setCellDigit(int row, int column, int cellValue);
  void setRow(int row, int digits[9]);
  void setColumn(int col, int digits[9]);
  void setSquare(int x, int y, int digits[9]);

  int getCellDigit(int cellIndex);
  int getCellDigit(int row, int column);
  
  void print();
  void pprint();

  // Scanning and algorithms
  int forAllSections(ScanFunction func, void *data);
  int forAllCells(ScanFunction func, void *data);

  bool validate();
  bool solve();
  static int sumGroup(ScanContext *context); // must be static to be used as function pointer
  
 private:
  SudokuCell cells[81];
  SudokuRow rows[9];
  SudokuColumn columns[9];
  SudokuSquare squares[9];
  
  int buf9[9]; // re-usable

  SudokuCell *getCell(int cellIndex);
  SudokuCell *getCell(int row, int column);
  SudokuCell *getCellBySquare(int square, int squareIndex);

  int doForAllSections(SudokuSection (*sections)[9],
		       ScanFunction func,
		       ScanContext *scanContext,
		       int type);
};

#endif // SUDOKU_H
