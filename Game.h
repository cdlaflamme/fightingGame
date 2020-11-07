//Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <list>	//for entity list
#include <iostream>

class Entity;
class DrawQ;

namespace Game {
	//values globally available
	//const bool DEBUG_ENABLED = false;
	const int FRAMERATE = 60;
	
	const int SCREEN_X = 800;
	const int SCREEN_Y = 600;
	
	sf::RenderWindow *window = NULL;
	DrawQ *drawQ = NULL;
	std::list<Entity*> *entityList = NULL;	
}

#endif