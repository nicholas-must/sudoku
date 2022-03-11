#include "sudoku.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// A nine-element integer buffer - will come in handy
static int buf9[9];

// Read nine integers into the buffer
static inline void read9()
{
  for (int i = 0; i < 9; ++i) cin >> buf9[i];
}

// Main loop
int main()
{
  cout << "Hello, Sudoku!!" << endl;

  // Game setup
  Sudoku sudoku;
  sudoku.print();

  // Game loop
  bool doSudoku = true;
  while (doSudoku)
  {
    string command;
    cin >> command;

    if (command == "help" || command == "h" || command == "?")
      printf("[p]rint \n"
	     "[s]et row col value \n"
	     "[r]ow row {1-9} \n"
	     "[c]ol col {1-9} \n"
	     "[sq]are x y {1-9} \n"
	     "[h/?]elp \n"
	     "e[x]it \n\n");

    if (command == "print" || command == "p")
      sudoku.print();

    if (command == "set" || command == "s")
    {
      int row, col, val;
      cin >> row;
      cin >> col;
      cin >> val;
      //SudokuCell::validate(
      sudoku.setCellValue(row, col, val);
      printf("Set cell %d, %d to %d\n", row , col, val);
    }

    if (command == "row" || command == "r")
    {
      int row; cin >> row;
      read9();
      sudoku.setRow(row, buf9);
    }

    if (command == "col" || command == "c")
    {
      int col; cin >> col;
      read9();
      sudoku.setColumn(col, buf9);
    }

    if (command == "square" || command == "sq")
    {
      int x; cin >> x;
      int y; cin >> y;
      read9();
      sudoku.setSquare(x, y, buf9);
    }
    
    if (command == "exit" || command == "x")
    {
      doSudoku = false;
      break;
    }
  }

  cout << "End" << endl;
  
  return 0;
}
