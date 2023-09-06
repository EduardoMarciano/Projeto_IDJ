CC = g++
CFLAGS = -I/usr/include/SDL2
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
TARGET = Game
SRC = Game.cpp

$(TARGET): $(SRC)
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)
