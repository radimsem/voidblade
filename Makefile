CXX = gcc
CXXFLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lm
SRC = src/main.c
OBJ = main.o
EXE = voidblade

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC)

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXE)
