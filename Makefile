FLAGS := -Wall -Wextra


dman: main.c
	gcc -o $@ ${FLAGS} $<
