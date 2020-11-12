CXX = g++

include_flags = -I C:/mingw64/usr/SFML-2.5.0/include/
linking_flags = -DSFML_STATIC -L C:/mingw64/usr/SFML-2.5.0/lib/ -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
CXXFLAGS = -Wall $(include_flags) $(linking_flags)

all: win_test.exe

clean:
	del *.o

win_test.exe: main.o DrawQ.o LoadScene.o Entity.o Game.o
	g++ main.o DrawQ.o LoadScene.o Entity.o Game.o -o win_test.exe $(CXXFLAGS)

main.o: main.cpp
DrawQ.o: DrawQ.cpp DrawQ.h
LoadScene.o: LoadScene.cpp LoadScene.h
Entity.o: Entity.cpp Entity.h
Game.o: Game.cpp Game.h