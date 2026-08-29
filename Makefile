all: main.o grafoPonderado_tad.o
	@gcc main.o grafoPonderado_tad.o -o exe
	@rm -r main.o grafoPonderado_tad.o
main.o: main.c
	@gcc main.c -c -Wall
grafoPonderado_tad.o: grafoPonderado_tad.c
	@gcc grafoPonderado_tad.c -c -Wall
run:
	@./exe
