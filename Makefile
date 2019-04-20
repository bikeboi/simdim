INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj

CC    := clang
FLAGS := -Wall -Wextra -I $(INC_DIR)
DEPS  := $(INC_DIR)/alloc.h $(INC_DIR)/parser.h

BIN_NAME = simdim

.PHONY: all clean

.all: debug

.clean:
	rm ./$(BIN_NAME) $(OBJ_DIR)/* || true

debug: FLAGS += -g
debug: simdim

$(OBJ_DIR)/simdim.o: $(SRC_DIR)/main.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

simdim: $(OBJ_DIR)/simdim.o
	$(CC) -o $@ $^ $(FLAGS)
