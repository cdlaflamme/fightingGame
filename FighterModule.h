//FighterModule.h

#ifndef FIGHTERMODULE_H
#define FIGHTERMODULE_H

#include "Game.h"

typedef struct {
	int owner; //player ID of owner (hitboxes can't hurt their owners)
	bool acceptsDamage; //is hurtbox
	bool dealsDamage; //is hitbox
	sf::FloatRect rect; //box
	int damage; //amount of damage this box deals; only needed if hitbox
	//consider a callback function that applies special effects to enemies?
} Hitbox;


typedef struct {
	int spriteIndex = 0;
	sf::Vector2f movement = sf::Vector2f(0,0);
	std::list<Hitbox> *hitboxes = NULL; //this variable type is a little tenative/messy
	//add other things like "is in armor" and such
} FighterState;


class FighterModule{
	sf::Texture fighterTexture;
	
	protected:
	FighterState lastState;
	int fighterState = 0; //big oof. something needs to be renamed. TODO
	sf::Clock stateClock;
	FighterModule(int id);
	
	public:
	sf::Texture *getTexture();
	virtual FighterState getNextState(EventList &eventList){
		FighterState state;
		state.movement = sf::Vector2f(0,0);
		state.spriteIndex = 0;
		state.hitboxes = NULL;
		return state;
	}; //the big one. calculates the next state based on recent input and stored information
};

FighterModule *createFighterModule(int ID); //FighterModule is an abstract class; this function instantiates an implemented class and passes it back as a generic module

#endif