#ifndef SUDOKU_DEFS_H
#define SUDOKU_DEFS_H

// Forward declarations
class SudokuSection;
class SudokuCell;

// TODO: Better name for these

struct ScanContext
{
  int type;
  int major;
  int minor;
  SudokuCell *cell;
  SudokuSection *section;
  void *data;
};

typedef int(*ScanFunction)(ScanContext*);

#endif // SUDOKU_DEFS_H
