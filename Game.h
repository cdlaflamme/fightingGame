//Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <list>	//for entity list
#include <iostream> //for logging

typedef std::list<sf::Event> EventList; //must do before including entity.h

#include "Entity.h"
#include "DrawQ.h"

typedef std::list<Entity*> EntityList;
typedef std::list<EntityList::iterator> EntItList;

namespace Game {
	//values globally available
	//const bool DEBUG_ENABLED = false;
	const int FRAMERATE = 60;
	
	const int SCREEN_X = 800;
	const int SCREEN_Y = 600;
	
	extern sf::RenderWindow *window;
	extern DrawQ *drawQ;
	extern EntityList *entityList;
	
	extern int fighter_ids[2];
	extern int stageID;
	
	void quit();
}

#endif