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
	bool hasHit; //has this hitbox hit someone already? if it has, it shouldn't hit again on subsequent frames (moves that hit multiple times should use multiple hitboxes)
	//consider a callback function that applies special effects to enemies?
} Hitbox;


//FighterSTate object used to pass information to the outside world. reasons why each of these things need to be passed outside:
//	sprite stuff: Fighter Entity's Update() puts sprite into the draw Q (could technically implement inside, but it's cleaner outside)
//	movement: Fighter Entity's Update() handles movement and world coordinates (again, could technically implement inside, but it's nice for the Fighter to not have to worry about coords stuff)
//	hitboxes: Fighter Entity's LateUpdate() handles hitboxes after a frame is set up (needs to be done outside in lateupdate(), or in some lateupdate() equivalent, so both fighters update before checking collision)
//Move status is internal to the fighter: outside world doesn't need to worry about that. It only manifests in the outside world as a sprite, movement vectors, and maybe armor-related booleans.
typedef struct {
	int spriteIndex = 0; //sprite index in the current "reel". each column of images in a sprite sheet has the same index (leftmost = 0)
	int spriteReel = 0; //sprite "reel" (i.e. animation) to use. Each row of images in a sprite sheet is a reel (topmost = 0)
	sf::Vector2f movement = sf::Vector2f(0,0);
	std::list<Hitbox> *hitboxes = NULL; //this variable type is a little tenative/messy
	//add other things like "is in armor" and such
} FighterState;


class FighterModule{
	sf::Texture fighterTexture;
	
	protected:
	FighterState lastState;
	sf::Clock moveClock;
	FighterModule(int id);
	
	public:
	sf::Texture *getTexture();
	virtual FighterState getNextState(EventList &eventList){ //the big one. calculates the next state based on recent input and stored information. should be overridden by inheritors
		FighterState state;
		state.movement = sf::Vector2f(0,0);
		state.spriteIndex = 0;
		state.hitboxes = NULL;
		return state;
	};
};

FighterModule *createFighterModule(int ID); //FighterModule is an abstract class; this function instantiates an implemented class and passes it back as a generic module

#endif