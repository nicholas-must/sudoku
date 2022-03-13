.PHONY: clean

run: main.o sudoku.o sudokuCell.o sudokuSection.o
	g++ main.o sudoku.o sudokuCell.o sudokuSection.o -o run

main.o: main.cpp sudoku.h sudokuCell.h sudokuSection.h sudokuDefs.h
	g++ -c main.cpp

sudoku.o: sudoku.cpp sudoku.h sudokuCell.h sudokuDefs.h
	g++ -c sudoku.cpp

sudokuSection.o: sudokuSection.cpp sudokuSection.h sudokuCell.h sudokuDefs.h
	g++ -c sudokuSection.cpp

sudokuCell.o: sudokuCell.cpp sudokuCell.h sudokuDefs.h
	g++ -c sudokuCell.cpp

clean:
	rm run *.o
