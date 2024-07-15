CC = clang

CCFLAGS = `sdl2-config --libs --cflags`
CCFLAGS += -ggdb3
CCFLAGS += -O0
CCFLAGS += -std=c99
CCFLAGS += -Wall
CCFLAGS += -lSDL2_image
CCFLAGS += -lm

SRC = $(wildcard src/*.c)
EXE = voidblade

all: $(EXE)

$(EXE): $(SRC)
	$(CC) -o $@ $^ $(CCFLAGS)

clean:
	rm -f $(EXE)

.PHONY: all clean
