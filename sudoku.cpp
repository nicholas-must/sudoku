#include "sudoku.h"

#include "sudokuSection.h"

#include <iostream>
#include <cstdlib>

using namespace std;

// Constructor
Sudoku::Sudoku()
{
  // Generate sections
  for (int sectionIndex = 0; sectionIndex < 9; ++sectionIndex)
  {
    for (int cellIndex = 0; cellIndex < 9; ++cellIndex)
    {
      // TODO: a virtual function pointer for cell lookup
      // could allow sections to arrange themselves
      SudokuCell *cell;
      // Rows
      cell = getCell(sectionIndex, cellIndex);
      rows[sectionIndex].setCell(cellIndex, cell);
	
      // Columns
      cell = getCell(cellIndex, sectionIndex);
      columns[sectionIndex].setCell(cellIndex, cell);

      // Squares
      cell = getCellBySquare(sectionIndex, cellIndex);
      squares[sectionIndex].setCell(cellIndex, cell);
    }
  }
}

// Public methods
void Sudoku::setCellDigit(int cellNumber, int cellValue)
{
  cells[cellNumber].setDigit(cellValue);
}

void Sudoku::setCellDigit(int row, int column, int cellValue)
{
  setCellDigit((row - 1) * 9 + (column - 1), cellValue);
}

void Sudoku::setRow(int row, int vals[9])
{
  for (int i = 0; i < 9; ++i)
    setCellDigit(row, i + 1, vals[i]);
}

void Sudoku::setColumn(int col, int vals[9])
{
  for (int i = 0; i < 9; ++i)
    setCellDigit(i + 1, col, vals[i]);
}

void Sudoku::setSquare(int x, int y, int vals[9])
{
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      setCellDigit(1 + (3 * (y - 1)) + i,
		   1 + (3 * (x - 1)) + j,
		   vals[3 * i + j]);
}

int Sudoku::getCellDigit(int cellNumber)
{
  return cells[cellNumber].getDigit();
}

int Sudoku::getCellDigit(int row, int column)
{
  return getCellDigit((row - 1) * 9 + (column - 1));
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
      cout << cells[offset].getDigit();
    }
    cout << "|" << endl;
  }
  cout << "-------------" << endl;
}

void Sudoku::pprint()
{
  // debug function to check the sections are working
  for (int i = 0; i < 9; ++i)
  {
    rows[i].print();
    columns[i].print();
    squares[i].print();
  }
}

int Sudoku::forAllSections(ScanFunction func, void *data)
{
  ScanContext context = {0};
  context.data = data;

  // TODO: Typedef this monstrosity
  doForAllSections((SudokuSection(*)[9])&rows, func, &context, 0);
  doForAllSections((SudokuSection(*)[9])&columns, func, &context, 1);
  doForAllSections((SudokuSection(*)[9])&squares, func, &context, 2);
  // TODO: Return properly
  return 0;
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
      int index = getCellDigit(row, col) - 1;
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

bool Sudoku::solve()
{
  // In theory, this should be all
  int sum;
  forAllSections(sumGroup, (void*)&sum);

  // Previous code:
  /*SumContext sumContext = {0, 0, 0};
  sumContext.type = 0;
  sumContext.majorIteration = 0;
  scan_rows(pSudoku, doSum, &sumContext);
  sumContext.type = 1;
  sumContext.majorIteration = 0;
  scan_columns(pSudoku, doSum, &sumContext);
  sumContext.type = 2;
  sumContext.majorIteration = 0;
  scan_squares(pSudoku, doSum, &sumContext);*/
  
  return false;
}

int Sudoku::sumGroup(ScanContext *context)
{
  /*printf("type=%d,major=%d,minor=%d,cell=%d,sum=%d\n",
	 context->type,
	 context->major,
	 context->minor,
	 context->cell->getDigit(),
	 *(int*)context->data);*/
  // Should have used gdb for this
  
  int *sum = (int*)context->data;
  // First
  if (context->minor == 1)
  {
    *sum = 0;
  }

  // Sum processing
  *sum += context->cell->getDigit();

  // Last - printing
  if (context->minor == 9)
  {
    printf("The sum of %s#%d is %d.\n",
	   context->section->getName().c_str(),
	   context->major,
	   *sum);
    if (*sum > 45) return 1; // Invalid sum
  }
  return 0;
}

// Private member functions
// TODO: make these more efficient - inline? non-member? macro?
SudokuCell * Sudoku::getCell(int cellIndex)
{
  return cells + cellIndex;
}

SudokuCell * Sudoku::getCell(int row, int column)
{
  return cells + (9 * row + column);
}

SudokuCell * Sudoku::getCellBySquare(int square, int squareIndex)
{
  int rowoffset = (square / 3) * 3;
  int coloffset = (square % 3) * 3;
  rowoffset += squareIndex / 3;
  coloffset += squareIndex % 3;
  int celloffset = 9 * rowoffset + coloffset;
  return cells + celloffset;
}

int Sudoku::doForAllSections(SudokuSection (*sections)[9],
			     ScanFunction func,
			     ScanContext *context,
			     int type)
{
  context->type = type;
  for (int i = 0; i < 9; ++i)
  {
    context->major = i + 1;
    context->section = (*sections) + i;
    context->section->forAll(func, context);
  }
  // TODO: Return properly
  return 0;
}

int Sudoku::doValidate(Sudoku *pSudoku,
		       int iteration,
		       int row,
		       int col,
		       void *context)
{
  // pSudoku should be this
  // context should be void tbh
  ScanContext *sumContext = (ScanContext*)context;

  if (0 == iteration)
  {
    // zerocontext
    std::fill(buf9, buf9+9, 0);
  }

  // do calc
  int index = getCellDigit(row, col) - 1;
  ++buf9[index];

  if (8 == iteration)
  {
    // group verdict
    for (int i = 0; i < 9; ++i)
    {
      string type =
      sumContext->type == 0 ? "ROW" :
      sumContext->type == 1 ? "COLUMN" :
      sumContext->type == 2 ? "SQUARE" : "UNKNOWN";
      
      if (buf9[i] != 1){
	printf("There are %d %d's in %s #%d\n",
	       buf9[i],
	       i+1,
	       type.c_str(),
	       sumContext->major);
	return 1; // bail on invalid
      }
    }
  }
  return 0;
}

int doSumOld(Sudoku *pSudoku,
	     int iteration,
	     int row,
	     int column,
	     void *context)
{
  // This is executed nine times
  // Given row and column of scan function
  // and a context passed from sum group
  ScanContext *sumContext = (ScanContext*)context;

  // Wipe on the first iteration
  if (0 == iteration)
  //fill(sumContext->buf9, sumContext->buf9+9, 0);
    sumContext->data = 0;

  // Tally up digits in section
  //int index = getCellDigit(row, column) - 1;
  //sumContext->buf9[index]++;

  // Sum up digits
  *(int*)(sumContext->data) += pSudoku->getCellDigit(row, column);

  // Validate on last iteration
  if (8 == iteration)
  {
    string type =
      sumContext->type == 0 ? "ROW" :
      sumContext->type == 1 ? "COLUMN" :
      sumContext->type == 2 ? "SQUARE" : "UNKNOWN";
    
    printf("The sum of %s#%d is %d\n",
	   type.c_str(),
	   ++sumContext->major,
	   *(int*)sumContext->data);

    if (*(int*)sumContext->data > 45) return 1; // bail on invalid
  }
  return 0;
}
