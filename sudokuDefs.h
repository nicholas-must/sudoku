#ifndef SUDOKU_DEFS_H
#define SUDOKU_DEFS_H

//#define DEBUG 1

#ifdef DEBUG
#define DLOG(...) printf(__VA_ARGS__)
#else
#define DLOG(...) 
#endif // DEBUG

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

struct Int9
{
  int x[9];
};

#endif // SUDOKU_DEFS_H
