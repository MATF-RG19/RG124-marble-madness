PROGRAM   = marble_madness
CC        = g++
CFLAGS    = -g -Wall -std=c++17
LDFLAGS   = -lGL -lGLU -lglut

$(PROGRAM): main.o field.o marble.o image.o
	$(CC) -o $(PROGRAM) $^ $(LDFLAGS) $(CFLAGS) 
field.o: field.cpp field.hpp
	$(CC) -c -o $@ $< $(LDFLAGS) $(CFLAGS)
main.o: main.cpp
	$(CC) -c -o $@ $< $(LDFLAGS) $(CFLAGS)
maeble.o: marble.cpp marble.hpp
	$(CC) -c -o $@ $< $(LDFLAGS) $(CFLAGS)
image.o: image.cpp image.hpp
	$(CC) -c -o $@ $< $(LDFLAGS) $(CFLAGS)

.PHONY: clean

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)

