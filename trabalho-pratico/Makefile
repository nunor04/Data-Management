CFLAGS=-Wall -Iinclude -g -Werror=discarded-qualifiers $(shell pkg-config --cflags glib-2.0) -pg
LDFLAGS=$(shell pkg-config --libs glib-2.0) -pg

SRC_FILES = src/programa-principal.c src/tipos/users.c src/tipos/reservations.c src/tipos/flights.c src/parser.c src/verificar.c src/catalogos/catalogo_users.c src/catalogos/catalogo_reservations.c src/catalogos/catalogo_flights.c src/interpreter.c src/output.c src/queries/query3.c src/queries/query4.c src/queries/query9.c src/queries/query7.c src/statistics.c

OBJ_FILES = $(SRC_FILES:.c=.o)

programa-principal: $(OBJ_FILES)
	gcc $^ -o $@ $(LDFLAGS)

valgrind: programa-principal
	valgrind --leak-check=full --show-leak-kinds=all -s ./programa-principal dataset/data dataset/input.txt

clean:
	rm -f $(OBJ_FILES) programa-principal gmon.out
	rm -rf Resultados/*