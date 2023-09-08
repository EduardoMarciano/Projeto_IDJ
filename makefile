CC = g++
CFLAGS = -std=c++11 -I/usr/include/SDL2
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
TARGET = Game
SRCS = main.cpp Game.cpp State.cpp Sprite.cpp Music.cpp

$(TARGET): $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)
