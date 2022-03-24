# Debug builds
ifneq (,$(DEBUG))
CFLAGS += -DDEBUG
CFLAGS += -g
endif

CPP = g++ $(CFLAGS)

.PHONY: clean

run: main.o sudoku.o sudokuCell.o sudokuSection.o algorithm.o
	$(CPP) main.o sudoku.o sudokuCell.o sudokuSection.o algorithm.o -o run

main.o: main.cpp sudoku.o sudokuCell.o sudokuSection.o sudokuDefs.h
	$(CPP) -c main.cpp

sudoku.o: sudoku.cpp sudoku.h sudokuCell.o algorithm.o sudokuDefs.h
	$(CPP) -c sudoku.cpp

sudokuSection.o: sudokuSection.cpp sudokuSection.h sudokuCell.o sudokuDefs.h
	$(CPP) -c sudokuSection.cpp

sudokuCell.o: sudokuCell.cpp sudokuCell.h sudokuDefs.h
	$(CPP) -c sudokuCell.cpp

algorithm.o: algorithm.cpp algorithm.h sudokuDefs.h
	$(CPP) -c algorithm.cpp

clean:
	-@rm run *.o >/dev/null 2>&1 || true
