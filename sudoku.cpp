#include "sudoku.h"

#include "sudokuSection.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <array>
#include <algorithm>

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
  // TODO: saveFile
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
      cout << "-------------------------------" << endl;
    
    
    // Print a row of numbers
    for (int j = 0; j < 9; ++j)
    {
      if (0 == (j) % 3)
	cout << "|";
      int offset = 9 * i + j;
      int digit = cells[offset].getDigit();
      printf(" %c ", (digit == 0 ? ' ' : '0' + digit));
      //cout << " " << (digit == 0 ? " " : ('0'+digit)) << " ";
    }
    cout << "|" << endl;
  }
  cout << "-------------------------------" << endl;
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

void Sudoku::printCellCandidates(int cellIndex)
{
  SudokuCell *cell = getCell(cellIndex);
  if (cell->getDigit())
    printf("cell #%d is %d\n", cellIndex, cell->getDigit());
  else
    printf("cell #%d has %zu candidates\n",
	   cellIndex,
	   cell->candidates.size());
}

void Sudoku::printCellCandidates(int row, int col)
{
  printCellCandidates(9 * (row - 1) + (col - 1));
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

int Sudoku::forAllCellSections(SudokuCell *cell, ScanFunction func, void *data, bool includeSelf)
{
  //DLOG("facs\n");
  // Populate an array with the cells to iterate over
  std::array<SudokuCell*, 27> cells;
  std::fill(cells.begin(), cells.end(), (SudokuCell*)0);
  /*std::copy(cell->row->getCells().set,
	    cell->row->getCells().set+9,
	    cells.end());
  std::copy(cell->column->begin(), cell->column->end(), cells.end());
  std::copy(cell->square->begin(), cell->square->end(), cells.end());
  */

  // TODO: Fix
  for (int i=0; i<9; ++i) {cells[i] = cell->row->getCell(i);}
  for (int i=0; i<9; ++i) {cells[9+i] = cell->column->getCell(i);}
  for (int i=0; i<9; ++i) {cells[18+i] = cell->square->getCell(i);}

  // Then execute func for all cells
  ScanContext context = {0};
  context.type = 5;
  context.data = data;
  std::for_each(cells.begin(),
		cells.end(),
		[&](SudokuCell* myCell){
		  if (!myCell) return; // Some null entries
		  //DLOG("scanning %p\n", myCell);
		  // Only include self once
		  if (myCell == cell) {
		    if (!includeSelf) return;
		    includeSelf = false;
		  }
		  // Populate ScanContext
		  context.cell = myCell;
		  func(&context);
		});
  // TODO: return properly
  //DLOG("facs]\n");
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
  forAllCells(soleCandidateScan, this);
  print();

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

// TODO: Use lambda
static int calculateCellCandidates(ScanContext *context)
{
  // Remove this cell's digit as a candidate
  SudokuCell *candidateCell = (SudokuCell*)context->data;
  int digit = context->cell->getDigit();
  
  // TODO: Consider replacing with a set function to remove a set of candidates
  if (digit)
  {
    if (candidateCell->candidates.count(digit))
    {
      DLOG("removing %d as candidate\n", digit);
      // Not needed here, but can be re-used here
      candidateCell->candidates.erase(digit);
    }
  }
  return 0;
}

int soleCandidateScan(ScanContext *context)
{
  // Don't process known digits
  if (0 != context->cell->getDigit()) return 0;

  context->cell->initiateCandidates();

  // Print cells
  size_t initialCandidates = context->cell->candidates.size();
  printf("cell %d has %zu candidates\n",
	 context->minor, initialCandidates);

  // Process candidates by cross-hatching, if required
  bool calculateCandidates = true;
  Sudoku *pSudoku = (Sudoku*)context->data;
  if (calculateCandidates)
  {
    pSudoku->forAllCellSections(context->cell, calculateCellCandidates, context->cell, 0);
  }

  // Print cells with less than 9 candidates
  if (context->cell->candidates.size() < initialCandidates)
    printf("cell %d now has %zu candidates\n",
	   context->minor, context->cell->candidates.size());

  // Solve sole candidate cells
  if (1 == context->cell->candidates.size())
  {
    int soleCandidate = *(context->cell->candidates.begin());
    context->cell->setDigit(soleCandidate);
    printf("solving cell %d with %d\n",
	   context->minor, context->cell->getDigit());
    // Recursive solve
    if (calculateCandidates)
    {
      printf("recursive solve\n");
      pSudoku->forAllCellSections(context->cell,
				  soleCandidateScan,
				  context->data, // pSudoku
				  0);
    }
  }

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
