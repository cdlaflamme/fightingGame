//Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <list>	//for entity list
#include <iostream>

#include "Entity.h"
#include "DrawQ.h"

namespace Game {
	//values globally available
	//const bool DEBUG_ENABLED = false;
	const int FRAMERATE = 60;
	
	const int SCREEN_X = 800;
	const int SCREEN_Y = 600;
	
	extern sf::RenderWindow *window;
	extern DrawQ *drawQ;
	extern std::list<Entity*> *entityList;
	
	extern int fighter_ids[2];
	extern int stageID;
	
	void quit();
}

#endif