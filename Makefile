CC=g++
CFLAGS=-Wall -O0 -g `pkg-config --cflags opencv`
SOURCES=main.cpp game.cpp duck.cpp world.cpp player.cpp radian.cpp vector2.cpp polarcoord.cpp mmapGpio.cpp
LDFLAGS=-lz -lpng -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lSDL2_mixer
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=duckhaunt


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.co:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
