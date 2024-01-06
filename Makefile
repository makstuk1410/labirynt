CFLAGS = -Wall -g
LDFLAGS = -lm


all: final

final: main.o mat.o labirynt.o sciana.o wagi.o error.o
	gcc $(CLFAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c mat.h
	gcc $(CFLAGS) -c -o $@ $<

mat.o: mat.c mat.h
	gcc $(CFLAGS) -c -o $@ $<

labirynt.o: labirynt.c labirynt.h
	gcc $(CFLAGS) -c -o $@ $<

sciana.o: sciana.c sciana.h
	gcc $(CFLAGS) -c -o $@ $<

wagi.o: wagi.c wagi.h
	gcc $(CFLAGS) -c -o $@ $<

error.o: error.c error.h
	gcc $(CFLAGS) -c -o $@ $<

clean: 
	rm -f main.o mat.o labirynt.o sciana.o error.o wagi.o final

