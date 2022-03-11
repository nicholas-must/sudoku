#include "sudoku.h"
#include <iostream>

using namespace std;

// Constructor
Sudoku::Sudoku(){}

// Destructor
Sudoku::~Sudoku() {}

// Public methods
void Sudoku::setCellValue(int cellNumber, int cellValue)
{
  cells[cellNumber].setValue(cellValue);
}

void Sudoku::setCellValue(int row, int column, int cellValue)
{
  setCellValue((row - 1) * 9 + (column - 1), cellValue);
}

void Sudoku::setRow(int row, int vals[9])
{
  for (int i = 0; i < 9; ++i)
    setCellValue(row, i + 1, vals[i]);
}

void Sudoku::setColumn(int col, int vals[9])
{
  for (int i = 0; i < 9; ++i)
    setCellValue(i + 1, col, vals[i]);
}

void Sudoku::setSquare(int x, int y, int vals[9])
{
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      setCellValue(1 + (3 * (y - 1)) + i,
		   1 + (3 * (x - 1)) + j,
		   vals[3 * i + j]);
}

int Sudoku::getCellValue(int cellNumber)
{
  return cells[cellNumber].getValue();
}

int Sudoku::getCellValue(int row, int column)
{
  return getCellValue((row - 1) * 9 + (column - 1));
}

void Sudoku::print()
{
  for (int i = 0; i < 9; ++i)
  {
    if (0 == (i) % 3)
      cout << "-------------" << endl;
    
    // Print a row of numbers
    for (int j = 0; j < 9; ++j)
    {
      if (0 == (j) % 3)
	cout << "|";
      int offset = 9 * i + j;
      cout << cells[offset].getValue();
    }
    cout << "|" << endl;
  }
  cout << "-------------" << endl;
}

bool Sudoku::validate()
{
  bool valid = true;
  // Check rows
  for (int row = 1; row <= 9; ++row)
  {
    // Fill buffer with totals; all should add to 9
    std::fill(buf9, buf9+9, 0);
    for (int col = 1; col <= 9; ++col)
    {
      int index = getCellValue(row, col) - 1;
      buf9[index]++;
    }
    // Check row digit counts
    for (int digit = 1; digit <= 9; ++digit)
    {
      int digitCount = buf9[digit - 1];
      if (digitCount != 1)
      {
	printf("There are %d %d's in row %d\n",
	       digitCount,
	       digit,
	       row);
      }
    }
  }

  // Check columns
  // reduce code triplication first

  // Check squares
  // reduce code triplication first

  return valid;
}


void sumGroup(Sudoku *pSudoku);

bool Sudoku::solve()
{
  sumGroup(this);
  return false;
}



////////////////////////////////////////
typedef int(*ScanFunction)(Sudoku *,int,int,int,void*);

void scan_columns(Sudoku *pSudoku, ScanFunction func, void *context)
{
  // Loops over columns and executes
  // the predicate 9 times
  for (int row = 1; row <= 9; ++row)
    for (int col = 1; col <= 9; ++col)
    {
      int iteration = col - 1;
      func(pSudoku, iteration, row, col, context);
    }

  return;
}

void scan_rows(Sudoku *pSudoku, ScanFunction func, void *context)
{
  // Loops over columns and executes
  // the predicate 9 times
  for (int col = 1; col <= 9; ++col)
    for (int row = 1; row <= 9; ++row)
    {
      int iteration = row - 1;
      func(pSudoku, iteration, row, col, context);
    }

  return;
}

void scan_squares(Sudoku *pSudoku, ScanFunction func, void *context)
{
  // Loops over columns and executes
  // the predicate 9 times
  for (int i = 0; i < 9; ++i)
  {
    int sqx = i % 3;
    int sqy = i / 3;
    
    for (int j = 0; j < 9; ++j)
    {
      int offx = j % 3;
      int offy = j / 3;
      int col = 1 + (sqx * 3) + offx;
      int row = 1 + (sqy * 3) + offy;
      
      func(pSudoku, i, row, col, context);
    }
  }

  return;
}

struct SumContext
{
  int majorIteration;
  int sum;
  int type; // 0r 1c 2s
};

int doSum(Sudoku *pSudoku,
	  int iteration,
	  int row,
	  int column,
	  void *context)
{
  // This is executed nine times
  // Given row and column of scan function
  // and a context passed from sum group
  SumContext *sumContext = (SumContext*)context;

  // Wipe on the first iteration
  if (0 == iteration)
  //fill(sumContext->buf9, sumContext->buf9+9, 0);
    sumContext->sum = 0;

  // Tally up digits in section
  //int index = getCellValue(row, column) - 1;
  //sumContext->buf9[index]++;

  // Sum up digits
  sumContext->sum += pSudoku->getCellValue(row, column);

  // Validate on last iteration
  if (8 == iteration)
  {
    string type =
      sumContext->type == 0 ? "ROW" :
      sumContext->type == 1 ? "COLUMN" :
      sumContext->type == 2 ? "SQUARE" : "UNKNOWN";
    
    printf("The sum of %s#%d is %d\n",
	   type.c_str(),
	   ++sumContext->majorIteration,
	   sumContext->sum);

    if (sumContext->sum > 45) return 1; // bail on invalid
  }
  return 0;
}

void sumGroup(Sudoku *pSudoku)
{
  SumContext sumContext = {0, 0, 0};
  sumContext.type = 0;
  sumContext.majorIteration = 0;
  scan_rows(pSudoku, doSum, &sumContext);
  sumContext.type = 1;
  sumContext.majorIteration = 0;
  scan_columns(pSudoku, doSum, &sumContext);
  sumContext.type = 2;
  sumContext.majorIteration = 0;
  scan_squares(pSudoku, doSum, &sumContext);
}
