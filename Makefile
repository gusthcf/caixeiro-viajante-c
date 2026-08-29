all: main.o grafoPonderado_tad.o
	@gcc main.o grafoPonderado_tad.o -o exe
	@rm -r main.o grafoPonderado_tad.o
main.o: src/main.c
	@gcc src/main.c -c -Wall
grafoPonderado_tad.o: src/grafoPonderado_tad.c
	@gcc src/grafoPonderado_tad.c -c -Wall
run:
	@./exe
