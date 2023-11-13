CC = g++
CFLAGS = -std=c++17 -I/usr/include/SDL2
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
TARGET = ../Game
SRCS = main.cpp Game.cpp TileSet.cpp TitleState.cpp State.cpp StageState.cpp Sprite.cpp Music.cpp Rect.cpp Sound.cpp Face.cpp Vec2.cpp GameObject.cpp Component.cpp Resources.cpp TileMap.cpp InputManager.cpp Camera.cpp CameraFollower.cpp Alien.cpp Minion.cpp Bullet.cpp
$(TARGET): $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)