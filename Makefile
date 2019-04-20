CC    := clang
FLAGS := -Wall -Wextra -I

SRC_DIR := src

BIN_NAME = simdim

.PHONY: all clean

.all: debug

.clean:
	rm ./$(BIN_NAME) || true

debug:	FLAGS += -g
debug:  $(BIN_NAME)

${BIN_NAME}: $(SRC_DIR)/main.c
	$(CC) -o $@ $(FLAGS) $<
