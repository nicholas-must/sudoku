# Debug builds
ifneq (,$(DEBUG))
CFLAGS += -DDEBUG
CFLAGS += -g
endif

CPP = g++ $(CFLAGS)

.PHONY: clean

run: main.o sudoku.o sudokuCell.o sudokuSection.o
	$(CPP) main.o sudoku.o sudokuCell.o sudokuSection.o -o run

main.o: main.cpp sudoku.h sudokuCell.h sudokuSection.h sudokuDefs.h
	$(CPP) -c main.cpp

sudoku.o: sudoku.cpp sudoku.h sudokuCell.h sudokuDefs.h
	$(CPP) -c sudoku.cpp

sudokuSection.o: sudokuSection.cpp sudokuSection.h sudokuCell.h sudokuDefs.h
	$(CPP) -c sudokuSection.cpp

sudokuCell.o: sudokuCell.cpp sudokuCell.h sudokuDefs.h
	$(CPP) -c sudokuCell.cpp

clean:
	rm run *.o
