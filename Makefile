CC=g++
CFLAGS=-Wall
LDFLAGS=-lSDL2
SOURCES=main.cpp game.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=duckhaunt


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.co:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

