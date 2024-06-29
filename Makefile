CC = clang

CCFLAGS = `sdl2-config --libs --cflags`
CCFLAGS += -ggdb3
CCFLAGS += -O0
CCFLAGS += -std=c99
CCFLAGS += -Wall
CCFLAGS += -lSDL2_image
CCFLAGS += -lm

SRC = src/main.c
OBJ = ./main.o
EXE = ./voidblade

all: $(EXE)

$(OBJ): $(SRC)
	$(CC) $(CCFLAGS) -c $(SRC)

$(EXE): $(OBJ)
	$(CC) $(CCFLAGS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)
