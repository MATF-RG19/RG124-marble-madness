PROGRAM   = marble_madness
CC        = g++
CFLAGS    = -g -Wall
LDFLAGS   = -lGL -lGLU -lglut

$(PROGRAM): main.o field.o marble.o
	$(CC) -o $(PROGRAM) $^ $(LDFLAGS) 
field.o: field.cpp field.hpp
	$(CC) -c -o $@ $< $(LDFLAGS)
main.o: main.cpp
	$(CC) -c -o $@ $< $(LDFLAGS)
maeble.o: marble.cpp marble.hpp
	$(CC) -c -o $@ $< $(LDFLAGS)

.PHONY: clean

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)

