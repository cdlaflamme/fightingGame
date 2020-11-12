
all: win_test.exe

clean:
	del *.o

win_test.exe: main.o DrawQ.o LoadScene.o Entity.o Game.o
	g++ main.o DrawQ.o LoadScene.o Entity.o Game.o -o win_test.exe -Wall -DSFML_STATIC -I C:/mingw64/usr/SFML-2.5.0/include/ -L C:/mingw64/usr/SFML-2.5.0/lib/ -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg

main.o: main.cpp
	g++ -c main.cpp -Wall -DSFML_STATIC -I C:/mingw64/usr/SFML-2.5.0/include/ -L C:/mingw64/usr/SFML-2.5.0/lib/ -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg

DrawQ.o: DrawQ.cpp
	g++ -c DrawQ.cpp -Wall -DSFML_STATIC -I C:/mingw64/usr/SFML-2.5.0/include/ -L C:/mingw64/usr/SFML-2.5.0/lib/ -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
	
LoadScene.o: LoadScene.cpp
	g++ -c LoadScene.cpp -Wall -DSFML_STATIC -I C:/mingw64/usr/SFML-2.5.0/include/ -L C:/mingw64/usr/SFML-2.5.0/lib/ -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg

Entity.o: Entity.cpp
	g++ -c Entity.cpp -Wall -DSFML_STATIC -I C:/mingw64/usr/SFML-2.5.0/include/ -L C:/mingw64/usr/SFML-2.5.0/lib/ -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg

Game.o: Game.cpp
	g++ -c Game.cpp -Wall -DSFML_STATIC -I C:/mingw64/usr/SFML-2.5.0/include/ -L C:/mingw64/usr/SFML-2.5.0/lib/ -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg