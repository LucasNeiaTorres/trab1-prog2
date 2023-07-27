parametrosCompilacao=-Wall -std=c99 -D_DEFAULT_SOURCE #-Wshadow
arquivos=arquivo.o lattes.o conf_peri.o pesquisador.o liblista.o compara_string.o interface.o
all: lattes

lattes: $(arquivos)
	gcc -o lattes $(arquivos) $(parametrosCompilacao)

.o: .c
	gcc -c *.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch lattes 

purge: clean
	-rm -f lattes