PROGRAM   = marble_madness
CC        = g++
CFLAGS    = -g -Wall
LDFLAGS   = -lGL -lGLU -lglut

$(PROGRAM): main.o field.cpp
	$(CC) -o $(PROGRAM) main.o $(LDFLAGS)
field.o: field.cpp
	$(CC) -o $< $(LDFLAGS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


