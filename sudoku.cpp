#include "sudoku.h"

#include "sudokuSection.h"

#include <iostream>
#include <fstream>
#include <sstream>
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
      cell->row = rows + sectionIndex;
	
      // Columns
      cell = getCell(cellIndex, sectionIndex);
      columns[sectionIndex].setCell(cellIndex, cell);
      cell->column = columns + sectionIndex;

      // Squares
      cell = getCellBySquare(sectionIndex, cellIndex);
      squares[sectionIndex].setCell(cellIndex, cell);
      cell->square = squares + sectionIndex;
    }
  }
}

// Public methods
int Sudoku::loadFile(string filename)
{
  ifstream sudokuFile(filename);
  
  string line;
  //stringstream stream;
  int index = 0, digit = 0;
  while (getline(sudokuFile, line))
  {
    cout << line << endl;
    stringstream stream;
    stream << line;
    
    while (1)
    {
      stream >> digit;
      if (!stream)
	break;
      setCellDigit(index++, digit);
      if (index >= 81) return 0; // Too many digits
    }
  }

  sudokuFile.close();
  return 0;
}

int Sudoku::saveFile(string filename)
{
  return 0;
}

void Sudoku::setCellDigit(int cellNumber, int cellValue)
{
  cells[cellNumber].setDigit(cellValue);
}

void Sudoku::setCellDigit(int row, int column, int cellValue)
{
  setCellDigit((row - 1) * 9 + (column - 1), cellValue);
}

// TODO: Use sections for these
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

// TODO: More space, for candidate rendering
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

int Sudoku::forAllCells(ScanFunction func, void *data)
{
  ScanContext context = {0};
  context.type = 4; // for cells
  context.section = 0; // not relevant
  context.major = 1;
  context.data = data;

  for (int index = 0; index < 81; ++index)
  {
    context.minor = index + 1;
    context.cell = cells + index;
    func(&context);
  }
  
  return 0;
}

bool Sudoku::validate()
{
  Int9 context = {0};
  forAllSections(validateBoard, (void*)&context);
  
  return true;
}

bool Sudoku::solve()
{
  // In theory, this should be all
  //int sum;
  //forAllSections(sumGroup, (void*)&sum);

  // Sole candidate testing
  forAllCells(soleCandidate, 0);

  return false;
}

int Sudoku::sumGroup(ScanContext *context)
{
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

// Non-member function!
int validateBoard(ScanContext *context)
{
  // Unpack context
  Int9 *buf9 = (Int9*)context->data;
  
  // First
  if (context->minor == 1)
    std::fill(buf9->x, buf9->x + 9, 0);
  
  // Process
  int digit = context->cell->getDigit();
  if (digit)
    ++(buf9->x[digit - 1]);

  // Last
  if (context->minor == 9)
  {
    for (int i = 0; i < 9; ++i)
    {
      if (buf9->x[i] > 1)
      {
	printf("There are %d %d's in %s #%d.\n",
		buf9->x[i],
		i + 1,
		context->section->getName().c_str(),
		context->major);
	return 1;
      }
    }
  }

  return 0;
}

int soleCandidate(ScanContext *context)
{
  // Don't process known digits
  if (0 != context->cell->getDigit()) return 0;
  
  int candidates[9]; // 1 is a cand., 0 is not
  std::fill(candidates, candidates+9, 1);

  // Calculate cell candidates - re-use this later..
  for (int index = 0; index < 9; ++index)
  {
    // TODO: Fix design here
    int digit = context->cell->row->getCell(index)->getDigit();
    if (digit) candidates[digit - 1] = 0;
    digit = context->cell->column->getCell(index)->getDigit();
    if (digit) candidates[digit - 1] = 0;
    digit = context->cell->square->getCell(index)->getDigit();
    if (digit) candidates[digit - 1] = 0;
  }

  // Check for sole candidates
  int numCandidates = 0;
  int soleCandidate = 0;
  for (int i = 0; i < 9; ++i)
  {
    if (candidates[i])
    {
      ++numCandidates;
      soleCandidate = i + 1;
    }
  }

  if (numCandidates < 9)
    printf("cell %d has %d candidates\n",
	   context->minor, numCandidates);
    
  if (1 == numCandidates)
    context->cell->setDigit(soleCandidate);

  return 0; // No reason to not continue algorithm
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
