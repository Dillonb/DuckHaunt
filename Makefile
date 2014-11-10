CC=g++
CFLAGS=-Wall -O0 -g
LDFLAGS=-lSDL2 -lSDL2_gfx
SOURCES=main.cpp game.cpp duck.cpp world.cpp player.cpp radian.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=duckhaunt


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.co:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

