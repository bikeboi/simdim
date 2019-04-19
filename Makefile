FLAGS := -Wall -Wextra

debug:	FLAGS += -g
debug:	dman

dman: main.c
	gcc -o $@ ${FLAGS} $<
