#ifndef SUDOKU_DEFS_H
#define SUDOKU_DEFS_H

#include <set>

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

// Typedefs
typedef int(*ScanFunction)(ScanContext*);

typedef std::set<int> SetInt;
typedef std::set<SetInt> SetSetInt;

struct Int9
{
  int x[9];
};

#endif // SUDOKU_DEFS_H
