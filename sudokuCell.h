#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <set>
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

  void initiateCandidates();
  
  void print();

  SudokuRow *row;
  SudokuColumn *column;
  SudokuSquare *square;

  // Poor encapsulation
  std::set<int> candidates;
  
 private:
  int digit; // 0 is unknown
  
};

#endif // SUDOKU_CELL_H
