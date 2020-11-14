CXX = g++

include_flags = -I C:/mingw64/usr/SFML-2.5.0/include/
linking_flags = -DSFML_STATIC -L C:/mingw64/usr/SFML-2.5.0/lib/ -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
CXXFLAGS = -Wall $(include_flags) $(linking_flags)

all: win_test.exe

debug:
	g++ -g main.cpp DrawQ.cpp LoadScene.cpp Entity.cpp Game.cpp FighterModule.cpp -o win_test_debug.exe $(CXXFLAGS)

clean:
	del *.o

win_test.exe: main.o DrawQ.o LoadScene.o Entity.o Game.o FighterModule.o
	g++ main.o DrawQ.o LoadScene.o Entity.o Game.o FighterModule.o -o win_test.exe $(CXXFLAGS)
	
win_test_debug.exe:

main.o: main.cpp Entity.cpp
DrawQ.o: DrawQ.cpp DrawQ.h
LoadScene.o: LoadScene.cpp LoadScene.h Entity.cpp
Entity.o: Entity.cpp Entity.h DrawQ.h LoadScene.h Game.h FighterModule.h
Game.o: Game.cpp Game.h
FighterModule.o: FighterModule.cpp FighterModule.h Game.h
