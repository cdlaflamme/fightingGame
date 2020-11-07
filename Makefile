
all: win_test.exe

win_test.exe: main.o DrawQ.o LoadScene.o Entity.o
	g++ main.o DrawQ.o LoadScene.o Entity.o -o win_test.exe -Wall -DSFML_STATIC -I C:\mingw64\usr\SFML-2.5.0\include\ -L C:\mingw64\usr\SFML-2.5.0\lib\ -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg

main.o: main.cpp
	g++ -c main.cpp -I C:\mingw64\usr\SFML-2.5.0\include\

DrawQ.o: DrawQ.cpp
	g++ -c DrawQ.cpp -I C:\mingw64\usr\SFML-2.5.0\include\
	
LoadScene.o: LoadScene.cpp
	g++ -c LoadScene.cpp -I C:\mingw64\usr\SFML-2.5.0\include\

Entity.o: Entity.cpp
	g++ -c Entity.cpp -I C:\mingw64\usr\SFML-2.5.0\include\

