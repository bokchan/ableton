CC=g++
CXXFLAGS=-I. -Wall

_SOURCES=clip.o \
	follow_action.o \
	follow_me_player.o \
	ticks_command.o \
	util.o
SOURCES=$(patsubst %,src/%,$(_SOURCES))

.PHONY: clean clean-all

follow_me: follow_me_app.cpp $(SOURCES)
	$(CC) -o $@ $^ $(CXXFLAGS)

test: tests/test.cpp $(SOURCES)
	$(CC) -o $@ $^ $(CXXFLAGS)

clean:
	rm -f ./follow_me ./test

clean-all: clean
	rm -f src/*.o
