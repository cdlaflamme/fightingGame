//Entity.h

#ifndef ENTITY_H
#define ENTITY_H

#include "Game.h"
#include "DrawQ.h"
#include "LoadScene.h"

class Entity;

typedef struct {
	int owner; //player ID of owner (hitboxes can't hurt their owners)
	bool acceptsDamage; //is hurtbox
	bool dealsDamage; //is hitbox
	sf::FloatRect rect; //box
} Hitbox;

typedef struct {
	int spriteIndex;
	sf::Vector2f movement;
	
	
} FighterState;

#endif