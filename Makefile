.PHONY: clean

run: main.o sudoku.o sudokuCell.o
	g++ main.o sudoku.o sudokuCell.o -o run

main.o: main.cpp sudoku.h sudokuCell.h
	g++ -c main.cpp

sudoku.o: sudoku.cpp sudoku.h sudokuCell.h
	g++ -c sudoku.cpp

sudokuCell.o: sudokuCell.cpp sudokuCell.h
	g++ -c sudokuCell.cpp

clean:
	rm run *.o
